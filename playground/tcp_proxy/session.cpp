#include "simple_log.h"

#include <asio/connect.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/write.hpp>
#include <memory>
#include <stdexcept>
#include <system_error>

using namespace std;
using asio::ip::tcp;

class TcpSession : public enable_shared_from_this<TcpSession> {
public:
  TcpSession(tcp::socket client_socket, string upstream_host, string upstream_port)
      : client_(std::move(client_socket)),
        upstream_(client_.get_executor()),
        resolver_(client_.get_executor()),
        upstream_host_(upstream_host),
        upstream_port_(upstream_port) {}

  void Start() {
    asio::error_code ec;
    const auto peer = client_.remote_endpoint(ec);
    if (!ec) {
      LOG_INFO0("new client %s:%u", peer.address().to_string().c_str(), peer.port());
    }
    connectUpstream();
  }

private:
  void connectUpstream() {
    auto self = shared_from_this();
    resolver_.async_resolve(upstream_host_, upstream_port_,
                            [self](const error_code& ec, tcp::resolver::results_type results) {
                              if (ec) {
                                self->fail("resolve upstream", ec);
                                return;
                              }

                              asio::async_connect(
                                  self->upstream_, results,
                                  [self](const error_code& ec, const tcp::endpoint& ep) {
                                    if (ec) {
                                      self->fail("connect upstream", ec);
                                      return;
                                    }

                                    LOG_INFO0("connected to upstream %s:%u",
                                              ep.address().to_string().c_str(), ep.port());
                                    self->readClient();
                                    self->readServer();
                                  });
                            });
  }

  void readClient() {
    auto self = shared_from_this();
    client_.async_read_some(asio::buffer(c2s_), [self](const error_code& ec, std::size_t bytes) {
      if (!ec) {
        // forward to server(upstream)
        self->writeServer(bytes);
        return;
      }
      if (ec == asio::error::eof) {
        LOG_DEBUG0("read eof on client, now close server...");
        self->shutdownSend(self->upstream_);
        return;
      }
      self->fail("read client", ec);
    });
  }

  void writeServer(std::size_t n) {
    auto self = shared_from_this();
    asio::async_write(self->upstream_, asio::buffer(c2s_.data(), n),
                      [self](error_code ec, std::size_t) {
                        if (ec) {
                          self->fail("write server", ec);
                          return;
                        }
                        self->readClient();
                      });
  }

  void readServer() {
    auto self = shared_from_this();
    upstream_.async_read_some(asio::buffer(s2c_), [self](const error_code& ec, std::size_t bytes) {
      if (!ec) {
        // forward to client
        self->writeClient(bytes);
        return;
      }
      if (ec == asio::error::eof) {
        LOG_DEBUG0("read eof on server, now close client...");
        self->shutdownSend(self->client_);
        return;
      }
      self->fail("read server", ec);
    });
  }

  void writeClient(std::size_t n) {
    auto self = shared_from_this();
    asio::async_write(self->client_, asio::buffer(s2c_.data(), n),
                      [self](error_code ec, std::size_t) {
                        if (ec) {
                          self->fail("write server", ec);
                          return;
                        }
                        self->readServer();
                      });
  }

  void fail(string_view where, const asio::error_code& ec) {
    LOG_ERROR("%s: %s", where.data(), ec.message().c_str());
    error_code ignored;
    client_.close(ignored);
    upstream_.close(ignored);
  }

  static void shutdownSend(tcp::socket& sock) {
    error_code ec;
    if (sock.shutdown(tcp::socket::shutdown_send, ec) && ec != asio::error::not_connected) {
      LOG_ERROR("halfclose failed: %s", ec.message().c_str());
    }
  }

private:
  tcp::socket client_;
  tcp::socket upstream_;

  tcp::resolver resolver_;
  string upstream_host_;
  string upstream_port_;

  array<byte, 16 * 1024> c2s_;
  array<byte, 16 * 1024> s2c_;
};

class TcpProxyServer {
public:
  TcpProxyServer(asio::io_context& io, const tcp::endpoint& listen_ep, std::string host,
                 std::string port)
      : io_(io), acceptor_(io), host_(host), port_(port) {
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

  void Start() {
    asio::error_code ec;
    const auto ep = acceptor_.local_endpoint(ec);
    if (!ec) {
      LOG_INFO("server listening on %s:%u", ep.address().to_string().c_str(), ep.port());
    }
    acceptNext();
  }

private:
  void acceptNext() {
    acceptor_.async_accept([this](const error_code& ec, tcp::socket sock) {
      if (!ec) {
        std::make_shared<TcpSession>(std::move(sock), host_, port_)->Start();
      } else {
        LOG_ERROR("accept fail: %s", ec.message().c_str());
      }

      if (acceptor_.is_open()) {
        acceptNext();
      }
    });
  }

private:
  asio::io_context& io_;
  tcp::acceptor acceptor_;
  std::string host_;
  std::string port_;
};