#pragma once

#include "utils.h"
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


namespace yychi {

namespace fs = std::filesystem;

enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF };

namespace details {

struct Sink {
  Sink() = default;
  Sink(const Sink&) = delete;
  Sink& operator=(const Sink&) = delete;
  virtual ~Sink() = default;

  virtual void Write(std::string_view msg, int fd) = 0;
};

struct ConsoleSink : public Sink {
  void Write(std::string_view msg, int fd) override;
};

struct FileSink : public Sink {
  FileSink(const std::string& filepath, size_t buf_size);
  ~FileSink() override { Flush(); }
  void Write(std::string_view msg, int fd) override;
  void Flush();

private:
  fs::path filepath_;
  size_t buf_size_;
  std::ofstream file_;
  size_t written_bytes_ = 0;
};

struct RotateFileSink : public Sink {
  RotateFileSink(const std::string& filepath, size_t bufsize, size_t maxsize, unsigned maxkeep);
  ~RotateFileSink() override { Flush(); }
  void Write(std::string_view msg, int fd) override;
  void Flush();

private:
  bool open();
  void rotate();
  // app.log.1 -> app.log.2
  void rename_forward(size_t i);
  std::string archive_name(unsigned i) const {
    if (i == 0) {
      return filepath_.string();
    }
    return filepath_.string() + '.' + std::to_string(i);
  }

private:
  fs::path filepath_;
  size_t bufsize_;
  size_t maxsize_;
  unsigned maxkeep_;
  std::ofstream file_;
  size_t cursize_ = 0;
  size_t written_bytes_ = 0;
};

}  // namespace details

class SimpleLogger {
public:
  typedef std::chrono::system_clock::time_point TimePoint;
  typedef std::unique_ptr<details::Sink> SinkPtr;

public:
  SimpleLogger() : SimpleLogger(LogLevel::INFO) {}
  SimpleLogger(LogLevel l);
  SimpleLogger(const SimpleLogger&) = delete;
  SimpleLogger(SimpleLogger&&) = delete;
  ~SimpleLogger();

  SimpleLogger& operator=(const SimpleLogger&) = delete;
  SimpleLogger& operator=(SimpleLogger&&) = delete;

  // template <class... Args>
  // void Log(LogLevel lv, Args&&... args);

  void Log(LogLevel level, const char* file, int lineno, const char* fmt, ...);

  void SetLogLevel(LogLevel lv) { level_ = lv; }
  LogLevel GetLogLevel() const { return level_; }

  template <class... Args>
  void LogInfo(const char* file, int ln, Args&&... args) {
    Log(LogLevel::INFO, file, ln, std::forward<Args>(args)...);
  }

  template <class... Args>
  void LogWarn(const char* file, int ln, Args&&... args) {
    Log(LogLevel::WARN, file, ln, std::forward<Args>(args)...);
  }

  void WriteLog(std::string&& msg, int fd=0);

  bool AddConsoleSink() {
    sinks_.push_back(std::make_unique<details::ConsoleSink>());
    return true;
  }

  bool AddFileSink(const std::string& filepath, size_t bufsize=0) {
    sinks_.push_back(std::make_unique<details::FileSink>(filepath, bufsize));
    return true;
  }

  bool AddRotateFileSink(const std::string& filepath, size_t bufsize, size_t maxsize, unsigned maxkeep) {
    sinks_.push_back(std::make_unique<details::RotateFileSink>(filepath, bufsize, maxsize, maxkeep));
    return true;
  }


private:
  struct LogRecord {
    std::string_view file;
    int lineno;
    std::string msg;
    TimePoint tp;
    LogLevel level;
  };

  struct ProcThread : public utils::WorkThreadT<LogRecord> {
    ProcThread(SimpleLogger* owner) : owner_(owner) {}
    void OnDispatchWorkItem(LogRecord&) override;
    bool OnThreadInitialize(const char* name) override {
      return WorkThreadT::OnThreadInitialize("log_writer");
    }

  private:
    SimpleLogger* owner_;
  };

  static constexpr const char* LevelText(LogLevel lv);
  void log(LogLevel level, const char* fmt, va_list args);


private:
  LogLevel level_;
  std::vector<SinkPtr> sinks_;

  std::unique_ptr<ProcThread> proc_thd_;
};


}  // namespace yychi

yychi::SimpleLogger& default_logger();

#define LOG_TRACE(fmt, ...) \
  default_logger().Log(yychi::LogLevel::TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...) \
  default_logger().Log(yychi::LogLevel::DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
  default_logger().Log(yychi::LogLevel::INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...) \
  default_logger().Log(yychi::LogLevel::WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
  default_logger().Log(yychi::LogLevel::ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_FATAL(fmt, ...) \
  default_logger().Log(yychi::LogLevel::FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

