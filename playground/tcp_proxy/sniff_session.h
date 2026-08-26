#pragma once

#include <asio/ip/tcp.hpp>
#include <string>

namespace V2 {

struct Upstream {
  std::string host;
  std::string port;
};

struct ClassifyResult {
  enum class Kind { NeedMoreData, Route, Reject };

  Kind kind = Kind::Reject;
  Upstream upstream{};
  std::string_view reason{""};
};

class TcpMuxSession : public std::enable_shared_from_this<TcpMuxSession> {
  using tcp = asio::ip::tcp;

public:
  TcpMuxSession(tcp::socket client_socket);
  void Start();

private:
  void connect(const Upstream& u);

  void readClient();
  void writeServer(std::size_t, bool shutdown);

  void readServer();
  void writeClient(std::size_t, bool shutdown);

  void fail(std::string_view where, const asio::error_code& ec);
  void rejectAndClose(std::string_view reason);
  static void shutdownSend(tcp::socket& sock);

  void tryRoute();
  ClassifyResult classify(std::string_view packet);

private:
  tcp::socket client_;
  tcp::socket upstream_;

  tcp::resolver resolver_;

  std::array<std::byte, 16 * 1024> c2s_{};
  std::array<std::byte, 16 * 1024> s2c_{};
  std::array<char, 4 * 1024> sniff_{};
  std::size_t sniff_size_ = 0;
};

class TcpProxyServer {
  using tcp = asio::ip::tcp;

public:
  TcpProxyServer(asio::io_context& io, const tcp::endpoint& listen_ep);
  void Start();

private:
  void acceptNext();

private:
  asio::io_context& io_;
  tcp::acceptor acceptor_;
};

}  // namespace V2