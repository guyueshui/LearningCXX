#include "config_read.h"
#include "str_utils.h"

#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <cassert>
#include <string>

using std::string;

bool Address::FromHostPort(const string& hp) {
  auto v = utils::Split(hp, ":");
  if (v.size() != 2) {
    return false;
  }
  host = v[0];
  port = v[1];
  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool LoadConfig(const string& filepath, Config& c) {
  try {
    YAML::Node root = YAML::LoadFile(filepath);

    auto listen_addr = root["listen_addr"];
    if (!listen_addr || !listen_addr.IsSequence()) {
      fprintf(stderr, "listen_addr must be sequence\n");
      return false;
    }

    // TODO: respect cmd args
    for (auto it = listen_addr.begin(); it != listen_addr.end(); ++it) {
      string hp = it->as<string>();
      Address addr;
      if (!addr.FromHostPort(hp)) {
        fprintf(stderr, "invalid address: %s\n", hp.c_str());
        return false;
      }
      c.listen_addrs.push_back(std::move(addr));
    }

    auto protocols = root["protocols"];
    c.ssh_backend = protocols["ssh"].as<string>("");
    c.rdp_backend = protocols["rdp"].as<string>("");
    auto http = protocols["http"];
    if (http && http.IsSequence()) {
      for (auto it = http.begin(); it != http.end(); ++it) {
        string path = (*it)["path"].as<string>();
        string backend = (*it)["backend"].as<string>();
        auto [_, inserted] = c.http_backends.emplace(std::move(path), std::move(backend));
        assert(inserted);
      }
    }

    auto log = root["log"];
    if (log) {
      auto l = log["level"].as<std::string>("trace");
      utils::ToLowerI(l);
      if (l.compare(0, 5, "trace") == 0) {
        c.log_level = yychi::LogLevel::TRACE;
      } else if (l.compare(0, 5, "debug") == 0) {
        c.log_level = yychi::LogLevel::DEBUG;
      } else if (l.compare(0, 4, "info") == 0) {
        c.log_level = yychi::LogLevel::INFO;
      } else if (l.compare(0, 4, "warn") == 0) {
        c.log_level = yychi::LogLevel::WARN;
      } else if (l.compare(0, 5, "error") == 0) {
        c.log_level = yychi::LogLevel::ERROR;
      } else if (l.compare(0, 5, "fatal") == 0) {
        c.log_level = yychi::LogLevel::FATAL;
      } else {
        throw std::invalid_argument("invalid log level: " + string(l));
      }
      c.log_file = log["file"].as<string>("");
      c.log_max_size = log["max_size"].as<unsigned>(1024);
      c.log_max_keep = log["max_keep"].as<unsigned>(10);
    }

  } catch (const YAML::BadFile& e) {
    fprintf(stderr, "open config file failed: %s\n", e.what());
    return false;
  } catch (const YAML::ParserException& e) {
    fprintf(stderr, "parse config file '%s' failed: %s\n", filepath.c_str(), e.what());
    return false;
  } catch (YAML::BadConversion& e) {
    fprintf(stderr, "YAML type conversion failed, file '%s', err '%s'\n", filepath.c_str(),
            e.what());
    return false;
  } catch (std::exception& e) {
    fprintf(stderr, "load config failed, file '%s', err '%s'\n", filepath.c_str(), e.what());
    return false;
  }
  return true;
}

void LogInit(const Config& c) {
  auto& log = yychi::Logger::Inst().GetLogger();
  log.SetLogLevel(c.log_level);
  if (!c.log_file.empty()) {
    log.AddRotateFileSink(c.log_file, 0, c.log_max_size * 1024, c.log_max_keep);
  }
  LOG_INFO0("log level is set to %s", yychi::Logger::LevelText(c.log_level));
}