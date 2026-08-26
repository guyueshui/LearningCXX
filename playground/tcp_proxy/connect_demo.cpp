#include "simple_log.h"

#include <asio/connect.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <exception>
#include <thread>

using namespace std;
using asio::ip::tcp;

void asio_connect(string host, string port) {
  try {
    asio::io_context io;
    tcp::resolver r(io);
    tcp::socket socket(io);
    auto ep = r.resolve(host, port);

    asio::connect(socket, ep);

    auto remote_ep = socket.remote_endpoint();
    LOG_INFO("connected to %s:%u(%s)", remote_ep.address().to_string().c_str(), remote_ep.port(),
             remote_ep.address().is_v6() ? "ipv6" : "ipv4");

    this_thread::sleep_for(3s);
  } catch (std::exception& e) {
    LOG_ERROR("exception: %s", e.what());
  }
}

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    printf("Usage: %s host port\n", argv[0]);
    return 0;
  }
  asio_connect(argv[1], argv[2]);
  yychi::Logger::Inst().Shutdown();
  return 0;
}