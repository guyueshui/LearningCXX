#pragma once

#include <string>
#include <vector>

namespace utils {

bool StartWith(const std::string& s, const std::string& prefix);
bool EndWith(const std::string& s, const std::string& suffix);
std::vector<std::string> Split(const std::string& s, const std::string& delim = " ");

}  // namespace utils