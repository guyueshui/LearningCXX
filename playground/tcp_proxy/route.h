#pragma once

#include "sniff_session.h"

#include <string_view>

V2::ClassifyResult Sniff(std::string_view packet, uint64_t id_);