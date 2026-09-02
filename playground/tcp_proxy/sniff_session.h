#pragma once

#include "macros.h"

#include <asio/any_io_executor.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/steady_timer.hpp>
#include <asio/strand.hpp>
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace V2 {

struct Upstream {
  std::string host;
  std::string port;
  bool FromHostPort(const std::string& hp);
};

struct ClassifyResult {
  enum class Kind { NeedMoreData, Route, Reject };

  Kind kind = Kind::Reject;
  Upstream upstream{};
  std::string reason{""};
};

class TcpMuxSession : public std::enable_shared_from_this<TcpMuxSession> {
  using tcp = asio::ip::tcp;

public:
  TcpMuxSession(tcp::socket client_socket);
  ~TcpMuxSession() { PRINT_FUNC(std::to_string(id_).c_str()); }
  void Start();
  void Stop();
  uint64_t Id() const { return id_; }

private:
  void connect(const Upstream& u);

  // On connected to upstream.
  void onConnect(const asio::error_code& ec, const tcp::endpoint& ep);

  void readClient();
  void writeServer(std::size_t, bool shutdown);

  void readServer();
  void writeClient(std::size_t, bool shutdown);

  void fail(std::string_view where, const asio::error_code& ec);
  void rejectAndClose(std::string_view reason);
  static void shutdownSend(tcp::socket& sock);

  void tryRoute();
  void onSniffTimeout(const asio::error_code& ec);
  ClassifyResult classify(std::string_view packet);
  void stopImpl();

  static uint64_t getId() {
    static std::atomic_uint64_t id{1};
    return id.fetch_add(1, std::memory_order_relaxed);
  }

private:
  uint64_t id_;
  asio::strand<asio::any_io_executor> strand_;
  tcp::socket client_;
  tcp::socket upstream_;
  tcp::resolver resolver_;
  asio::steady_timer sniff_timer_;

  std::array<std::byte, 16 * 1024> c2s_{};
  std::array<std::byte, 16 * 1024> s2c_{};
  std::array<char, 4 * 1024> sniff_{};
  std::size_t sniff_size_ = 0;
  bool stopped_ = false;
};


class SessionManager {
public:
  typedef std::shared_ptr<TcpMuxSession> SessPtr;
  typedef std::weak_ptr<TcpMuxSession> SessWPtr;

  void Add(const SessPtr& s);
  void Remove(uint64_t id);

  void StopAll();

private:
  std::mutex mu_;
  std::unordered_map<uint64_t, SessWPtr> sess_{};
  bool ready_ = true;
};


class TcpProxyServer {
  using tcp = asio::ip::tcp;

public:
  TcpProxyServer(asio::io_context& io, const tcp::endpoint& listen_ep);
  void Start();
  void Stop();

private:
  void acceptNext();

private:
  asio::io_context& io_;
  tcp::acceptor acceptor_;
  asio::strand<asio::any_io_executor> strand_;
  SessionManager sess_mgr_;
};

}  // namespace V2