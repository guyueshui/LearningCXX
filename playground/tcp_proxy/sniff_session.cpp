#include "simple_log.h"
#include "sniff_session.h"
#include "str_utils.h"

#include <asio/connect.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/write.hpp>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <system_error>

#include "atomizes.hpp"

using namespace std;
using asio::ip::tcp;

namespace V2 {

TcpMuxSession::TcpMuxSession(tcp::socket client_socket)
    : client_(std::move(client_socket)),
      upstream_(client_.get_executor()),
      resolver_(client_.get_executor()) {}

void TcpMuxSession::Start() {
  asio::error_code ec;
  const auto peer = client_.remote_endpoint(ec);
  if (!ec) {
    LOG_INFO0("new client %s:%u", peer.address().to_string().c_str(), peer.port());
  }
  tryRoute();
}

void TcpMuxSession::connect(const Upstream& u) {
  auto self = shared_from_this();
  resolver_.async_resolve(
      u.host, u.port, [self](const error_code& ec, tcp::resolver::results_type results) {
        if (ec) {
          self->fail("resolve upstream", ec);
          return;
        }

        asio::async_connect(
            self->upstream_, results, [self](const error_code& ec, const tcp::endpoint& ep) {
              if (ec) {
                self->fail("connect upstream", ec);
                return;
              }

              LOG_INFO0("connected to upstream %s:%u", ep.address().to_string().c_str(), ep.port());

              // flush sniffed data
              asio::async_write(self->upstream_, asio::buffer(self->sniff_, self->sniff_size_),
                                [self](const error_code& ec, std::size_t written) {
                                  if (ec) {
                                    self->fail("write sniff bytes", ec);
                                    return;
                                  }
                                  if (written != self->sniff_size_) {
                                    self->fail("write sniff bytes corrupt",
                                               asio::error::operation_aborted);
                                    return;
                                  }
                                  self->readClient();
                                  self->readServer();
                                });
            });
      });
}

void TcpMuxSession::readClient() {
  auto self = shared_from_this();
  client_.async_read_some(asio::buffer(c2s_), [self](const error_code& ec, std::size_t bytes) {
    if (!ec) {
      // forward to server(upstream)
      self->writeServer(bytes, false);
      return;
    }
    if (ec == asio::error::eof) {
      if (bytes > 0) {
        LOG_WARN0("[c -> s]read eof but got %zubyte(s) data, will half-close after forwared",
                  bytes);
        self->writeServer(bytes, true);
      } else {
        LOG_DEBUG0("[c -> s]read eof on client, now half-close server...");
        self->shutdownSend(self->upstream_);
      }
      return;
    }
    self->fail("read client", ec);
  });
}

void TcpMuxSession::writeServer(std::size_t n, bool shutdown) {
  auto self = shared_from_this();
  asio::async_write(self->upstream_, asio::buffer(c2s_.data(), n),
                    [self, n, shutdown](error_code ec, std::size_t written) {
                      if (ec) {
                        self->fail("write server", ec);
                        return;
                      }
                      if (written != n) {
                        LOG_WARN0("[c->s] short write to server, wrote %zu, expect %zu", written,
                                  n);
                      }
                      if (shutdown) {
                        LOG_DEBUG0("[c->s] client EOF forwarded, half-close server send");
                        self->shutdownSend(self->upstream_);
                      } else {
                        self->readClient();
                      }
                    });
}

void TcpMuxSession::readServer() {
  auto self = shared_from_this();
  upstream_.async_read_some(asio::buffer(s2c_), [self](const error_code& ec, std::size_t bytes) {
    if (!ec) {
      // forward to client
      self->writeClient(bytes, false);
      return;
    }
    if (ec == asio::error::eof) {
      if (bytes > 0) {
        LOG_WARN0("[s->c] read eof but got %zu byte(s) data, will half-close after forwarded",
                  bytes);
        self->writeClient(bytes, true);
      } else {
        LOG_DEBUG0("[s->c] read eof on server, now half-close client...");
        self->shutdownSend(self->client_);
      }
      return;
    }
    self->fail("read server", ec);
  });
}

void TcpMuxSession::writeClient(std::size_t n, bool shutdown) {
  auto self = shared_from_this();
  asio::async_write(self->client_, asio::buffer(s2c_.data(), n),
                    [self, n, shutdown](error_code ec, std::size_t written) {
                      if (ec) {
                        self->fail("write client", ec);
                        return;
                      }
                      if (written != n) {
                        LOG_WARN0("[s -> c]short write to client, wrote %zu, expect %zu", written,
                                  n);
                      }
                      if (shutdown) {
                        LOG_DEBUG0("[s -> c]server EOF forwarded, half-close client send");
                        self->shutdownSend(self->client_);
                      } else {
                        self->readServer();
                      }
                    });
}

void TcpMuxSession::fail(string_view where, const asio::error_code& ec) {
  LOG_ERROR("%s: %s", where.data(), ec.message().c_str());
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
  LOG_INFO("reject: %s", reason.data());
  error_code ignored;
  client_.close(ignored);
}

void TcpMuxSession::tryRoute() {
  if (sniff_size_ == sniff_.size()) {
    rejectAndClose("first packet too large or unknown protocol");
    return;
  }

  auto self = shared_from_this();

  client_.async_read_some(asio::buffer(sniff_.data() + sniff_size_, sniff_.size() - sniff_size_),
                          [self](const asio::error_code& ec, std::size_t n) {
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
                          });
}

ClassifyResult TcpMuxSession::classify(string_view packet) {
  using K = ClassifyResult::Kind;
  ClassifyResult r;
  if (packet.size() >= 4 && memcmp(packet.data(), "SSH-", 4) == 0) {
    r.upstream = {"127.0.0.1", "3222"};
    r.kind = K::Route;
    return r;
  }

  // try parse http packet
  const auto pos = packet.find("\r\n\r\n");
  if (pos != string_view::npos) {
    const string header{packet.substr(0, pos + 4)};
    atomizes::HTTPMessageParser parser;
    atomizes::HTTPMessage msg;
    parser.Parse(&msg, header);
    LOG_DEBUG0(
        "\n\theader_count:%zu"
        "\n\tmethod:%d"
        "\n\tpath:%s"
        "\n\tversion:%s"
        "\n\tstatus_msg:%s"
        "\n\tstatus_code:%u"
        "\n\tua:%s"
        "\n\thost:%s"
        "\n\taccpet:%s"
        "\n",
        msg.HeaderCount(), msg.GetMethod(), msg.GetPath().c_str(), msg.GetVersion().c_str(),
        msg.GetStatusMessage().c_str(), msg.GetStatusCode(), msg.GetHeader("User-Agent").c_str(),
        msg.GetHeader("Host").c_str(), msg.GetHeader("Accept").c_str());
    const string& path = msg.GetPath();
    if (utils::StartWith(path, "/immich")) {
      r.upstream = {"127.0.0.1", "2283"};
      r.kind = K::Route;
      return r;
    } else if (utils::StartWith(path, "/nextcloud")) {
      r.upstream = {"127.0.0.1", "7080"};
      r.kind = K::Route;
      return r;
    } else {
      r.upstream = {"127.0.0.1", "5244"};
      r.kind = K::Route;
      return r;
    }
  } else {
    // NeedMoreData
  }

  LOG_DEBUG0("unrecognized packet: %.*s", static_cast<int>(packet.size()), packet.data());
  r.reason = "unknown protocol";
  return r;
}

////////////////////////////////////////////////////////////////////////////////
TcpProxyServer::TcpProxyServer(asio::io_context& io, const tcp::endpoint& listen_ep)
    : io_(io), acceptor_(io) {
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
  asio::error_code ec;
  const auto ep = acceptor_.local_endpoint(ec);
  if (!ec) {
    LOG_INFO("server listening on %s:%u", ep.address().to_string().c_str(), ep.port());
  }
  acceptNext();
}

void TcpProxyServer::acceptNext() {
  acceptor_.async_accept([this](const error_code& ec, tcp::socket sock) {
    if (!ec) {
      std::make_shared<TcpMuxSession>(std::move(sock))->Start();
    } else {
      LOG_ERROR("accept fail: %s", ec.message().c_str());
    }

    if (acceptor_.is_open()) {
      acceptNext();
    }
  });
}

}  // namespace V2