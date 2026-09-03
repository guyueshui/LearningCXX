#pragma once

#include "config_read.h"

#include <string_view>

ClassifyResult Sniff(std::string_view packet, uint64_t id_);