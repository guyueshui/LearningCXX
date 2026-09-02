#include "config_read.h"

#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <cassert>

using std::string;

bool load_config(const string& filepath, Config& c) {
  try {
    YAML::Node root = YAML::LoadFile(filepath);

    auto listen_addr = root["listen_addr"];
    if (!listen_addr || !listen_addr.IsSequence()) {
      fprintf(stderr, "listen_addr must be sequence\n");
      return false;
    }
    c.local_addr = (*listen_addr.begin()).as<string>();

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
      auto l = log["level"].as<std::string_view>("trace");
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
      printf("max_size=%u, max_keep=%u\n", c.log_max_size, c.log_max_keep);
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
    fprintf(stderr, "load_config failed, file '%s', err '%s'\n", filepath.c_str(), e.what());
    return false;
  }
  return true;
}