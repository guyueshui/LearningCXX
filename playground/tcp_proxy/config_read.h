#pragma once

#include "simple_log.h"
#include "str_utils.h"

#include <string>
#include <unordered_map>

struct Address {
  std::string host;
  std::string port;
  bool FromHostPort(const std::string& hp);
};

struct ClassifyResult {
  enum class Kind { NeedMoreData, Route, Reject };

  Kind kind = Kind::Reject;
  Address upstream{};
  std::string reason{""};
};

struct Config {
  Address cli_local;
  std::vector<Address> listen_addrs;

  std::string ssh_backend;
  std::string rdp_backend;
  // TODO: ignore case compare
  // std::unordered_map<std::string, std::string> http_backends;
  std::unordered_map<std::string, std::string, utils::IgnorecaseHash, utils::IgnorecaseEqual>
      http_backends;

  yychi::LogLevel log_level;
  std::string log_file;
  unsigned log_max_size;
  unsigned log_max_keep;
};

bool LoadConfig(const std::string& filepath, Config& c);
void LogInit(const Config& c);