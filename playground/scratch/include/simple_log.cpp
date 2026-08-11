#include "macros.h"
#include "simple_log.h"
#include "utils.h"
#include <unistd.h>

#include <chrono>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <utility>

namespace yychi {

using namespace std;

namespace {
string GetFileBaseName(const string& filepath) {
#if __cplusplus >= 201703L
  return fs::path(filepath).filename().string();
#else
  auto pos = filepath.find_last_of('/');
  if (pos != string::npos) {
    return filepath.substr(pos + 1);
  }
  return filepath;
#endif
}
}  // namespace

SimpleLogger::SimpleLogger(LogLevel l) : level_(l), proc_thd_(make_unique<ProcThread>(this)) {
  proc_thd_->Start();
}

SimpleLogger::~SimpleLogger() {
  if (proc_thd_) {
    proc_thd_->Stop();
  }
  proc_thd_.reset();
}

void SimpleLogger::Log(LogLevel level, const char* file, int lineno, const char* fmt, ...) {
  if (level < level_) {
    return;
  }

  char buf[1024];
  va_list vl;
  va_start(vl, fmt);
  vsnprintf(buf, 1024, fmt, vl);
  va_end(vl);

  LogRecord rec{
      file, lineno, buf, std::chrono::system_clock::now(), level,
  };

  proc_thd_->Post(std::move(rec));
}

// clang-format off
constexpr const char* SimpleLogger::LevelText(LogLevel lv) {
  switch (lv) {
  case LogLevel::TRACE: return "TRACE";
  case LogLevel::DEBUG: return "DEBUG";
  case LogLevel::INFO: return "INFO";
  case LogLevel::WARN: return "WARN";
  case LogLevel::ERROR: return "ERROR";
  case LogLevel::FATAL: return "FATAL";
  case LogLevel::OFF:;
  }
  return "UNKNOWN";
}
// clang-format on

void SimpleLogger::WriteLog(string&& msg, int fd) {
  for (auto& s : sinks_) {
    s->Write(msg, fd);
  }
}

////////////////////////////////////////////////////
void SimpleLogger::ProcThread::OnDispatchWorkItem(LogRecord& rec) {
  time_t t = chrono::system_clock::to_time_t(rec.tp);
  struct tm lt;
  utils::get_local_time(t, &lt);
  // char* a = "1996-01-24 00:00:00.000";
  char buf[24] = {0};
  const size_t written_bytes = std::strftime(buf, 24, "%F %T", &lt);
  const long ms = chrono::duration_cast<chrono::milliseconds>(rec.tp.time_since_epoch()).count() % 1000;
  snprintf(buf + written_bytes, sizeof(buf) - written_bytes, ".%03ld", ms);
  const string& raw = rec.msg;
  std::ostringstream os;
  os << buf << " [" << LevelText(rec.level) << "] " << GetFileBaseName(rec.file.data()) << ':'
     << rec.lineno << " - " << raw;
  if (raw.empty() || raw.back() != '\n') {
    os << '\n';
  }
  // 1: stdout, 2: stderr
  owner_->WriteLog(os.str(), rec.level >= LogLevel::ERROR ? 2 : 1);
}

namespace details {

////////////////////////////////////////////////////
void ConsoleSink::Write(string_view msg, int fd) {
  write(fd, msg.data(), msg.size());
}

////////////////////////////////////////////////////
FileSink::FileSink(const string& filepath, size_t buf_size)
    : filepath_(filepath), buf_size_(buf_size), file_(filepath, ios::out | ios::app) {}

void FileSink::Write(string_view msg, int fd) {
  if (!file_.is_open()) {
    file_.open(filepath_, ios::out | ios::app);
  }
  if (!file_.is_open()) {
    return;  // something wrong
  }
  if (!file_.write(msg.data(), msg.size())) {
    throw runtime_error("write log failed: " + filepath_.string());
  }
  written_bytes_ += msg.size();
  if (buf_size_ == 0 || written_bytes_ >= buf_size_) {
    Flush();
  }
}

void FileSink::Flush() {
  if (file_.is_open()) {
    file_.flush();
  }
  written_bytes_ = 0;
}

////////////////////////////////////////////////////
RotateFileSink::RotateFileSink(const string& filepath, size_t bufsize, size_t maxsize,
                                        unsigned maxkeep)
    : filepath_(filepath), bufsize_(bufsize), maxsize_(maxsize), maxkeep_(maxkeep)
{
  if (maxsize == 0) {
    throw invalid_argument("maxsize msut be greater than zero!");
  }
  if (!open()) {
    throw runtime_error("failed to open file when construct: " + filepath);
  }
}

void RotateFileSink::Write(string_view msg, int fd) {
  if (!file_.is_open() && !open()) {
    fprintf(stderr, "write log when file not open!");
    return;
  }
  if (cursize_ != 0 && cursize_ + msg.size() > maxsize_) {
    rotate();
  }

  if (!file_.write(msg.data(), msg.size())) {
    throw runtime_error("write log failed: " + filepath_.string());
  }
  written_bytes_ += msg.size();
  if (bufsize_ == 0 || written_bytes_ >= bufsize_) {
    Flush();
  }
  cursize_ += msg.size();
}

void RotateFileSink::Flush() {
  if (file_.is_open()) {
    file_.flush();
  }
  written_bytes_ = 0;
}

bool RotateFileSink::open() {
  error_code ec;
  const auto parent = filepath_.parent_path();
  if (!parent.empty()) {
    fs::create_directories(parent, ec);
    if (ec) {
      fprintf(stderr, "create log directory failed: %s\n", ec.message().c_str());
      return false;
    }
  }

  uintmax_t fsize = 0;
  if (fs::exists(filepath_, ec) && !ec) {
    fsize = fs::file_size(filepath_, ec);
    if (ec) {
      fprintf(stderr, "failed to get file size: %s\n", ec.message().c_str());
      return false;
    }
  }

  file_.open(filepath_, ios::out | ios::app);
  if (!file_.is_open()) {
    fprintf(stderr, "failed to open file: %s\n", filepath_.c_str());
    return false;
  }

  written_bytes_ = 0;
  cursize_ = static_cast<size_t>(fsize);
  return true;
}

void RotateFileSink::rotate() {
  Flush();
  file_.close();

  error_code ec;
  if (maxkeep_ == 0) {
    fs::remove(filepath_, ec);
    if (ec) {
      fprintf(stderr, "remove old file failed: %s\n", ec.message().c_str());
    }
    open();
    return;
  }

  string to_rm = archive_name(maxkeep_);
  if (fs::exists(to_rm, ec) && !ec) {
    fs::remove(to_rm, ec);
    if (ec) {
      fprintf(stderr, "remote old file failed: %s\n", ec.message().c_str());
    }
  }

  rename_forward(0);

  open();
}

void RotateFileSink::rename_forward(size_t i) {
  string from = archive_name(i);
  string to = archive_name(i + 1);
  if (!fs::exists(from)) {
    return;
  }
  if (fs::exists(to)) {
    rename_forward(i + 1);
  }
  if (std::rename(from.c_str(), to.c_str()) != 0) {
    fprintf(stderr, "rename file %s to %s failed\n", from.c_str(), to.c_str());
  }
}

}  // namespace details

}  // namespace yychi


yychi::SimpleLogger& default_logger() {
  static yychi::SimpleLogger s_logger(yychi::LogLevel::TRACE);
  static int _ = []{
    s_logger.AddConsoleSink();
    return 0;
  }();
  return s_logger;
}