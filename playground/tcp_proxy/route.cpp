#include "config_read.h"
#include "route.h"

#include <string_view>

#include "atomizes.hpp"

using std::string_view, std::string;

namespace {

// Provided by perplexity.ai
bool MatchRdp(string_view packet) {
  constexpr size_t min_rdp_bytes = 11;
  if (packet.size() < min_rdp_bytes) {
    return false;
  }
  auto p = reinterpret_cast<const unsigned char*>(packet.data());
  if (p[0] != 0x03 || p[1] != 0x00) {
    return false;
  }
  const size_t tpkt_len = (static_cast<size_t>(p[2]) << 8) | p[3];
  if (tpkt_len < min_rdp_bytes || tpkt_len > 8192) {
    return false;
  }
  if (p[5] != 0xE0 || p[4] < 6) {
    return false;
  }
  return true;
}

ClassifyResult GetRoute(const string& hp, const string& tag) {
  using K = ClassifyResult::Kind;
  ClassifyResult r;
  if (hp.empty()) {
    r.kind = K::Reject;
    r.reason = tag + ":no available backend";
  } else if (r.upstream.FromHostPort(hp)) {
    r.kind = K::Route;
  } else {
    r.kind = K::Reject;
    r.reason = tag + ":failed to parse backend";
  }
  return r;
}

string_view FirstPathSegment(string_view p) {
  auto query_pos = p.find('?');
  const string_view path = p.substr(0, query_pos);
  if (path.empty() || path.front() != '/') {
    return {};
  }

  const auto slash_pos = path.find('/', 1);
  if (slash_pos == string_view::npos) {
    return path;
  }
  return path.substr(0, slash_pos);
}

}  // namespace

extern Config g_config;

ClassifyResult Sniff(string_view packet, uint64_t id_) {
  using K = ClassifyResult::Kind;

  if (packet.size() >= 4 && memcmp(packet.data(), "SSH-", 4) == 0) {
    return GetRoute(g_config.ssh_backend, "ssh");
  }

  if (MatchRdp(packet)) {
    return GetRoute(g_config.rdp_backend, "rdp");
  }

  // try parse http packet
  const auto pos = packet.find("\r\n\r\n");
  if (pos != string_view::npos) {
    const string header{packet.substr(0, pos + 4)};
    atomizes::HTTPMessageParser parser;
    atomizes::HTTPMessage msg;
    parser.Parse(&msg, header);
    const string& path = msg.GetPath();
    const string seg{FirstPathSegment(path)};
    LOG_DEBUG0(
        "[%lu]"
        "\n\theader_count:%zu"
        "\n\tmethod:%d"
        "\n\tpath:%s"
        "\n\tversion:%s"
        "\n\tstatus_msg:%s"
        "\n\tstatus_code:%u"
        "\n\tua:%s"
        "\n\thost:%s"
        "\n\taccept:%s"
        "\n\tseg:%s"
        "\n",
        id_, msg.HeaderCount(), msg.GetMethod(), path.c_str(), msg.GetVersion().c_str(),
        msg.GetStatusMessage().c_str(), msg.GetStatusCode(), msg.GetHeader("User-Agent").c_str(),
        msg.GetHeader("Host").c_str(), msg.GetHeader("Accept").c_str(), seg.c_str());
    auto it = g_config.http_backends.find(seg);
    if (it != g_config.http_backends.end()) {
      return GetRoute(it->second, it->first);
    }
  }

  LOG_DEBUG0("unrecognized packet: %.*s, try sniff more...", static_cast<int>(packet.size()),
             packet.data());
  ClassifyResult r;
  r.kind = K::NeedMoreData;
  return r;
}
