#include "macros.h"
#include "route.h"
#include "simple_log.h"
#include "sniff_session.h"
#include "str_utils.h"

#include <asio/bind_executor.hpp>
#include <asio/connect.hpp>
#include <asio/detail/chrono.hpp>
#include <asio/dispatch.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/strand.hpp>
#include <asio/write.hpp>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <vector>


using namespace std;
using asio::ip::tcp;


namespace V2 {

bool Upstream::FromHostPort(const string& hp) {
  auto v = utils::Split(hp, ":");
  if (v.size() != 2) {
    return false;
  }
  host = v[0];
  port = v[1];
  return true;
}

////////////////////////////////////////////////////////////////////////////////
TcpMuxSession::TcpMuxSession(tcp::socket client_socket)
    : id_(getId()),
      strand_(asio::make_strand(client_socket.get_executor())),
      client_(std::move(client_socket)),
      upstream_(strand_),
      resolver_(strand_),
      sniff_timer_(strand_) {
  PRINT_FUNC(to_string(id_).c_str());
}

void TcpMuxSession::Start() {
  asio::error_code ec;
  const auto peer = client_.remote_endpoint(ec);
  if (!ec) {
    LOG_INFO0("[%lu]new client %s:%u", id_, peer.address().to_string().c_str(), peer.port());
  }
  auto self = shared_from_this();
  sniff_timer_.expires_after(asio::chrono::seconds(3));
  sniff_timer_.async_wait(
      asio::bind_executor(strand_, [self](const error_code& ec) { self->onSniffTimeout(ec); }));
  tryRoute();
}

void TcpMuxSession::Stop() {
  auto self = shared_from_this();
  asio::post(strand_, [self] { self->stopImpl(); });
}

void TcpMuxSession::stopImpl() {
  if (stopped_) {
    return;
  }
  stopped_ = true;
  sniff_timer_.cancel();

  asio::error_code ignored;
  client_.shutdown(tcp::socket::shutdown_both, ignored);
  client_.close(ignored);

  upstream_.shutdown(tcp::socket::shutdown_both, ignored);
  upstream_.close(ignored);
}

void TcpMuxSession::connect(const Upstream& u) {
  auto self = shared_from_this();
  resolver_.async_resolve(
      u.host, u.port,
      asio::bind_executor(
          strand_, [self](const error_code& ec, tcp::resolver::results_type results) {
            if (ec) {
              self->fail("resolve upstream", ec);
              return;
            }

            asio::async_connect(self->upstream_, results,
                                asio::bind_executor(self->strand_, [self](const error_code& ec,
                                                                          const tcp::endpoint& ep) {
                                  self->onConnect(ec, ep);
                                }));
          }));
}

void TcpMuxSession::onConnect(const asio::error_code& ec, const tcp::endpoint& ep) {
  if (ec) {
    fail("connect upstream", ec);
    return;
  }

  LOG_INFO0("[%lu]connected to upstream %s:%u", id_, ep.address().to_string().c_str(), ep.port());

  // flush sniffed data
  asio::async_write(upstream_, asio::buffer(sniff_, sniff_size_),
                    asio::bind_executor(strand_, [self = shared_from_this()](const error_code& ec,
                                                                             std::size_t written) {
                      if (ec) {
                        self->fail("write sniff bytes", ec);
                        return;
                      }
                      if (written != self->sniff_size_) {
                        self->fail("write sniff bytes corrupt", asio::error::operation_aborted);
                        return;
                      }
                      self->readClient();
                      self->readServer();
                    }));
}

void TcpMuxSession::readClient() {
  auto self = shared_from_this();
  client_.async_read_some(
      asio::buffer(c2s_),
      asio::bind_executor(strand_, [self](const error_code& ec, std::size_t bytes) {
        if (!ec) {
          // forward to server(upstream)
          self->writeServer(bytes, false);
          return;
        }
        if (ec == asio::error::eof) {
          if (bytes > 0) {
            LOG_WARN0("[%lu][c->s]read eof but got %zubyte(s) data, will half-close after forwared",
                      self->id_, bytes);
            self->writeServer(bytes, true);
          } else {
            LOG_DEBUG0("[%lu][c->s]read eof on client, now half-close server...", self->id_);
            self->shutdownSend(self->upstream_);
          }
          return;
        }
        self->fail("read client", ec);
      }));
}

void TcpMuxSession::writeServer(std::size_t n, bool shutdown) {
  auto self = shared_from_this();
  asio::async_write(
      self->upstream_, asio::buffer(c2s_.data(), n),
      asio::bind_executor(strand_, [self, n, shutdown](error_code ec, std::size_t written) {
        if (ec) {
          self->fail("write server", ec);
          return;
        }
        if (written != n) {
          LOG_WARN0("[%lu][c->s] short write to server, wrote %zu, expect %zu", self->id_, written,
                    n);
        }
        if (shutdown) {
          LOG_DEBUG0("[%lu][c->s] client EOF forwarded, half-close server send", self->id_);
          self->shutdownSend(self->upstream_);
        } else {
          self->readClient();
        }
      }));
}

void TcpMuxSession::readServer() {
  auto self = shared_from_this();
  upstream_.async_read_some(
      asio::buffer(s2c_),
      asio::bind_executor(strand_, [self](const error_code& ec, std::size_t bytes) {
        if (!ec) {
          // forward to client
          self->writeClient(bytes, false);
          return;
        }
        if (ec == asio::error::eof) {
          if (bytes > 0) {
            LOG_WARN0(
                "[%lu][s->c] read eof but got %zu byte(s) data, will half-close after forwarded",
                self->id_, bytes);
            self->writeClient(bytes, true);
          } else {
            LOG_DEBUG0("[%lu][s->c] read eof on server, now half-close client...", self->id_);
            self->shutdownSend(self->client_);
          }
          return;
        }
        self->fail("read server", ec);
      }));
}

void TcpMuxSession::writeClient(std::size_t n, bool shutdown) {
  auto self = shared_from_this();
  asio::async_write(
      self->client_, asio::buffer(s2c_.data(), n),
      asio::bind_executor(strand_, [self, n, shutdown](error_code ec, std::size_t written) {
        if (ec) {
          self->fail("write client", ec);
          return;
        }
        if (written != n) {
          LOG_WARN0("[%lu][s->c]short write to client, wrote %zu, expect %zu", self->id_, written,
                    n);
        }
        if (shutdown) {
          LOG_DEBUG0("[%lu][s->c]server EOF forwarded, half-close client send", self->id_);
          self->shutdownSend(self->client_);
        } else {
          self->readServer();
        }
      }));
}

void TcpMuxSession::fail(string_view where, const asio::error_code& ec) {
  LOG_ERROR("[%lu]%s: %s", id_, where.data(), ec.message().c_str());
  sniff_timer_.cancel();
  error_code ignored;
  client_.close(ignored);
  upstream_.close(ignored);
}

void TcpMuxSession::shutdownSend(tcp::socket& sock) {
  error_code ec;
  if (sock.shutdown(tcp::socket::shutdown_send, ec) && ec != asio::error::not_connected) {
    LOG_ERROR("half-close failed: %s", ec.message().c_str());
  }
}

void TcpMuxSession::rejectAndClose(string_view reason) {
  LOG_INFO("[%lu]reject: %s", id_, reason.data());
  sniff_timer_.cancel();
  error_code ignored;
  client_.close(ignored);
}

void TcpMuxSession::tryRoute() {
  if (sniff_size_ == sniff_.size()) {
    rejectAndClose("first packet too large or unknown protocol");
    return;
  }

  auto self = shared_from_this();

  client_.async_read_some(
      asio::buffer(sniff_.data() + sniff_size_, sniff_.size() - sniff_size_),
      asio::bind_executor(strand_, [self](const asio::error_code& ec, std::size_t n) {
        if (ec && ec != asio::error::eof) {
          self->fail("sniff read", ec);
          return;
        }

        self->sniff_size_ += n;

        std::string_view data(self->sniff_.data(), self->sniff_size_);
        const auto result = self->classify(data);

        using K = ClassifyResult::Kind;
        switch (result.kind) {
        case K::Route:
          self->sniff_timer_.cancel();
          self->connect(result.upstream);
          return;

        case K::Reject:
          self->rejectAndClose(result.reason);
          return;

        case K::NeedMoreData:
          if (ec == asio::error::eof) {
            self->rejectAndClose("incomplete init packet");
            return;
          }
          self->tryRoute();
          return;
        }
      }));
}

ClassifyResult TcpMuxSession::classify(string_view packet) {
  return Sniff(packet, id_);
}

void TcpMuxSession::onSniffTimeout(const asio::error_code& ec) {
  if (ec == asio::error::operation_aborted) {
    // timer is canceled
    return;
  }
  if (ec) {
    // not canceled but another error, log it
    fail("sniff timer", ec);
    return;
  }
  rejectAndClose("sniff timeout");
}

////////////////////////////////////////////////////////////////////////////////
TcpProxyServer::TcpProxyServer(asio::io_context& io, const tcp::endpoint& listen_ep)
    : io_(io), acceptor_(io), strand_(asio::make_strand(acceptor_.get_executor())) {
  asio::error_code ec;
  if (acceptor_.open(listen_ep.protocol(), ec)) {
    throw std::runtime_error("acceptor open failed: " + ec.message());
  }

  if (acceptor_.set_option(tcp::acceptor::reuse_address(true), ec)) {
    throw std::system_error(ec);
  }

  if (acceptor_.bind(listen_ep, ec)) {
    throw std::system_error(ec);
  }

  if (acceptor_.listen(asio::socket_base::max_listen_connections, ec)) {
    throw std::system_error(ec);
  }
}

void TcpProxyServer::Start() {
  asio::dispatch(strand_, [this] {
    asio::error_code ec;
    const auto ep = acceptor_.local_endpoint(ec);
    if (!ec) {
      LOG_INFO("server listening on %s:%u", ep.address().to_string().c_str(), ep.port());
    }
    acceptNext();
  });
}

void TcpProxyServer::Stop() {
  asio::post(strand_, [this] {
    asio::error_code ec;
    if (acceptor_.cancel(ec)) {
      LOG_ERROR("acceptor cancel failed: %s", ec.message().c_str());
    }
    ec.clear();
    if (acceptor_.close(ec)) {
      LOG_ERROR("acceptor close failed: %s", ec.message().c_str());
    }
    sess_mgr_.StopAll();
  });
}

void TcpProxyServer::acceptNext() {
  acceptor_.async_accept(
      asio::bind_executor(strand_, [this](const error_code& ec, tcp::socket sock) {
        if (!ec) {
          auto s = std::make_shared<TcpMuxSession>(std::move(sock));
          sess_mgr_.Add(s);
          s->Start();
        } else if (ec != asio::error::operation_aborted) {
          LOG_ERROR("accept fail: %s", ec.message().c_str());
        }

        if (acceptor_.is_open()) {
          acceptNext();
        }
      }));
}

////////////////////////////////////////////////////////////////////////////////
void SessionManager::Add(const SessPtr& s) {
  if (!s) {
    return;
  }
  lock_guard<mutex> lock(mu_);
  if (!ready_) {
    return;
  }
  bool inserted = sess_.emplace(s->Id(), s).second;
  if (!inserted) {
    LOG_ERROR("duplicate session id %lu", s->Id());
  }
}

void SessionManager::Remove(uint64_t id) {
  SessPtr s;
  {
    lock_guard<mutex> lock(mu_);
    auto it = sess_.find(id);
    if (it == sess_.end()) {
      return;
    }
    s = it->second.lock();
    sess_.erase(it);
  }
  if (s) {
    s->Stop();
  }
}

void SessionManager::StopAll() {
  vector<SessPtr> sessions;
  {
    lock_guard<mutex> lock(mu_);
    ready_ = false;
    for (auto it = sess_.begin(); it != sess_.end(); ++it) {
      if (SessPtr s = it->second.lock()) {
        sessions.push_back(s);
      }
    }
    sess_.clear();
  }

  for (auto& s : sessions) {
    s->Stop();
  }
}

}  // namespace V2