#include "config_read.h"
#include "simple_log.h"
#include "sniff_session.h"

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
#include <string>

using asio::ip::tcp;
using std::string, std::cout, std::endl;

Config g_config;

struct CmdLine {
  clara::Parser MakeCmdlineParser(Config& c) {
    using namespace clara;
    auto const set_local_addr = [&](const string& token) {
      if (!c.cli_local.FromHostPort(token)) {
        return ParserResult::runtimeError("invalid local addr, should be like \"host:port\"");
      }
      return ParserResult::ok(ParseResultType::Matched);
    };

    cli = clara::Help(show_help)("Show this help and exit").required() |
          clara::Opt(arg_conf_file, "file")["-c"]["--config"]("Config file") |
          clara::Opt(n_threads, "threads")["-j"]("Number of io threads(1..16)") |
          clara::Arg(set_local_addr, "local-addr")("local address(host:port) to listen on");
    return cli;
  }

  void ShowHelp() const {
    cout << "\nA simple tcp relay.\n" << cli << "\nfooter message\n" << endl;
  }

  bool show_help = false;
  unsigned n_threads = 1;
  string arg_conf_file{};
  clara::Parser cli;
};

int main(int argc, const char* argv[]) {
  CmdLine cmd;
  auto cli = cmd.MakeCmdlineParser(g_config);

  auto result = cli.parse(clara::Args{argc, argv});
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    return 1;
  }
  if (cmd.show_help) {
    cmd.ShowHelp();
    return 0;
  }

  if (cmd.arg_conf_file.empty()) {
    cmd.arg_conf_file = "config.yml";
  }
  if (!LoadConfig(cmd.arg_conf_file, g_config)) {
    return 1;
  }
  LogInit(g_config);

  Address& hp =
      g_config.cli_local.host.empty() ? g_config.listen_addrs.front() : g_config.cli_local;

  try {
    asio::io_context io;
    tcp::resolver r(io);
    auto ep = r.resolve(hp.host, hp.port);
    // const tcp::endpoint local_addr{asio::ip::make_address("0.0.0.0"), 5566};
    auto local_addr = *ep.begin();
    auto proxy = std::make_shared<TcpProxyServer>(io, local_addr);
    proxy->Start();

    asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait([&io, proxy](const asio::error_code& ec, int signal) {
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

    if (cmd.n_threads <= 1) {
      io.run();
    } else {
      cmd.n_threads = std::min(cmd.n_threads, 16u);
      LOG_INFO0("run %u io threads...", cmd.n_threads);
      std::vector<std::thread> thds;
      while (cmd.n_threads--) {
        thds.push_back(std::thread([&io] { io.run(); }));
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