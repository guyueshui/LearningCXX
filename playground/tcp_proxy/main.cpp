#include "simple_log.h"
#include "sniff_session.h"
#include "str_utils.h"

#include <algorithm>
#include <asio/error.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <clara.hpp>
#include <csignal>
#include <exception>
#include <iostream>
#include <memory>

using asio::ip::tcp;
using namespace clara;

int main(int argc, const char* argv[]) {
  bool show_help = false;
  bool flag = false;
  std::string arg_local_addr;
  unsigned n_threads = 1;
  auto cli = Help(show_help)("show this help and exit").required() |
             Opt(flag)["-d"]["--doit"]("Do the thing") |
             Opt(n_threads, "threads")["-j"]("Number of io threads(1..16)") |
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
    // V2::TcpProxyServer proxy(io, local_addr); 
    auto proxy = std::make_shared<V2::TcpProxyServer>(io, local_addr);
    proxy->Start();

    asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait([&io, proxy](const asio::error_code& ec, int signal){
      if (ec == asio::error::operation_aborted) {
        return;
      }
      if (ec) {
        LOG_ERROR0("signal wait failed: %s", ec.message().c_str());
        return;
      }

      LOG_INFO("received signal %d, shutting down...", signal);
      proxy->Stop();
    });

    if (n_threads <= 1) {
      io.run();
    } else {
      n_threads = std::min(n_threads, 16u);
      LOG_INFO0("run %u io threads...", n_threads);
      std::vector<std::thread> thds;
      while (n_threads--) {
        thds.push_back(std::thread([&io]{ io.run(); }));
      }
      for (auto& t : thds) {
        t.join();
      }
    }
    LOG_INFO("server stopped");
  } catch (std::exception& e) {
    LOG_FATAL(e.what());
  }

  yychi::Logger::Inst().Shutdown();
  return 0;
}