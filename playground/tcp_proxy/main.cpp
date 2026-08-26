#include "simple_log.h"
#include "sniff_session.h"
#include "str_utils.h"

#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/tcp.hpp>
#include <clara.hpp>
#include <exception>
#include <iostream>

using asio::ip::tcp;
using namespace clara;

int main(int argc, const char* argv[]) {
  bool show_help = false;
  bool flag = false;
  std::string arg_local_addr;
  auto cli = Help(show_help)("show this help and exit") |
             Opt(flag)["-d"]["--doit"]("Do the thing") |
             Arg(arg_local_addr, "local-addr")("local address(host:port) to listen on");

  auto result = cli.parse(Args(argc, argv));
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    return 1;
  }
  if (show_help) {
    std::cout << cli << std::endl;
    return 0;
  }

  std::cout << flag << '\n';
  std::cout << arg_local_addr << '\n';
  auto hp = utils::Split(arg_local_addr, ":");
  if (hp.size() != 2) {
    std::cerr << "failed to parse local-addr" << std::endl;
    return 1;
  }

  try {
    asio::io_context io;
    tcp::resolver r(io);
    auto ep = r.resolve(hp[0], hp[1]);
    // const tcp::endpoint local_addr{asio::ip::make_address("0.0.0.0"), 5566};
    auto local_addr = *ep.begin();
    V2::TcpProxyServer proxy(io, local_addr); 
    proxy.Start();

    io.run();
  } catch (std::exception& e) {
    LOG_FATAL(e.what());
  }

  yychi::Logger::Inst().Shutdown();
  return 0;
}