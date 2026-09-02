#pragma once

#include "simple_log.h"
#include "str_utils.h"

#include <string>
#include <unordered_map>


struct Config {
  std::string local_addr;

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

bool load_config(const std::string& filepath, Config& c);