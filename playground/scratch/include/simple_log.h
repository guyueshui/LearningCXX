#pragma once

#include "macros.h"
#include "utils.h"
#include <array>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>


namespace yychi {

namespace fs = std::filesystem;

enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF };
enum SinkSlot : unsigned { CONSOLE = 0, FILE, FILE_ROT, _MAX };

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

class LoggerImpl {
public:
  typedef std::chrono::system_clock::time_point TimePoint;
  typedef std::unique_ptr<details::Sink> SinkPtr;

public:
  LoggerImpl() : LoggerImpl(LogLevel::TRACE) {}
  LoggerImpl(LogLevel l);
  LoggerImpl(const LoggerImpl&) = delete;
  LoggerImpl(LoggerImpl&&) = delete;
  ~LoggerImpl();

  LoggerImpl& operator=(const LoggerImpl&) = delete;
  LoggerImpl& operator=(LoggerImpl&&) = delete;

  // template <class... Args>
  // void Log(LogLevel lv, Args&&... args);

  void Log(LogLevel level, const char* file, int lineno, const char* fmt, ...);
  // void Log(LogLevel level, const char* file, int lineno, const char* fmt, va_list ap);

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
    auto& x = sinks_[SinkSlot::CONSOLE];
    if (x) {
      return false;
    }
    x.emplace(std::make_unique<details::ConsoleSink>());
    return true;
  }

  void RemoveSink(SinkSlot slot) {
    sinks_.at(slot).reset();
  }

  bool AddFileSink(const std::string& filepath, size_t bufsize=0) {
    auto& x = sinks_[SinkSlot::FILE];
    if (x) {
      return false;
    }
    x.emplace(std::make_unique<details::FileSink>(filepath, bufsize));
    return true;
  }

  bool AddRotateFileSink(const std::string& filepath, size_t bufsize, size_t maxsize, unsigned maxkeep) {
    auto& x = sinks_[SinkSlot::FILE_ROT];
    if (x) {
      return false;
    }
    x.emplace(std::make_unique<details::RotateFileSink>(filepath, bufsize, maxsize, maxkeep));
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
    ProcThread(LoggerImpl* owner) : owner_(owner) {}
    void OnDispatchWorkItem(LogRecord&) override;
    bool OnThreadInitialize(const char* name) override {
      return WorkThreadT::OnThreadInitialize("log_writer");
    }

  private:
    LoggerImpl* owner_;
  };

  static constexpr const char* LevelText(LogLevel lv);
  void log(LogLevel level, const char* fmt, va_list args);


private:
  LogLevel level_;
  std::array<std::optional<SinkPtr>, SinkSlot::_MAX> sinks_;
  std::unique_ptr<ProcThread> proc_thd_;
};


/* Singleton to manager loggers. */
class Logger : public utils::Singleton<Logger> {
public:
  typedef std::unique_ptr<LoggerImpl> LoggerPtr;
  friend class utils::Singleton<Logger>;

  LoggerImpl& GetLogger(const std::string& name);
  void Shutdown() { logger_map_.clear(); }

private:
  Logger() = default;
  ~Logger() { PRINT_FUNC(""); }

private:
  std::unordered_map<std::string, LoggerPtr> logger_map_;
};


struct LogHelper {
  LogHelper(LogLevel lv, const char* file, int line) : level_(lv), file_(file), line_(line) {}
  bool CheckLevel() const {
    auto& logger = getLogger();
    return level_ >= logger.GetLogLevel();
  }

  template<class... Args>
  void operator()(Args&&... args) {
    if (!CheckLevel()) {
      return;
    }
    getLogger().Log(level_, file_.data(), line_, std::forward<Args>(args)...);
  }

private:
  LoggerImpl& getLogger() const {
    return Logger::Inst().GetLogger("default");
  }

private:
  std::string_view file_;
  int line_;
  LogLevel level_;
};


}  // namespace yychi


#define LOG_TRACE yychi::LogHelper(yychi::LogLevel::TRACE, __FILE__, __LINE__)
#define LOG_DEBUG yychi::LogHelper(yychi::LogLevel::DEBUG, __FILE__, __LINE__)
#define LOG_INFO yychi::LogHelper(yychi::LogLevel::INFO, __FILE__, __LINE__)
#define LOG_WARN yychi::LogHelper(yychi::LogLevel::WARN, __FILE__, __LINE__)
#define LOG_ERROR yychi::LogHelper(yychi::LogLevel::ERROR, __FILE__, __LINE__)
#define LOG_FATAL yychi::LogHelper(yychi::LogLevel::FATAL, __FILE__, __LINE__)

// Marcos that do not eval arguments when log level is dismissed.
#define LOG_TRACE0(...)                                                    \
  do {                                                                     \
    auto x = yychi::LogHelper(yychi::LogLevel::TRACE, __FILE__, __LINE__); \
    if (x.CheckLevel()) {                                                  \
      x(__VA_ARGS__);                                                      \
    }                                                                      \
  } while (0)

#define LOG_DEBUG0(...)                                                    \
  do {                                                                     \
    auto x = yychi::LogHelper(yychi::LogLevel::DEBUG, __FILE__, __LINE__); \
    if (x.CheckLevel()) {                                                  \
      x(__VA_ARGS__);                                                      \
    }                                                                      \
  } while (0)

#define LOG_INFO0(...)                                                    \
  do {                                                                     \
    auto x = yychi::LogHelper(yychi::LogLevel::INFO, __FILE__, __LINE__); \
    if (x.CheckLevel()) {                                                  \
      x(__VA_ARGS__);                                                      \
    }                                                                      \
  } while (0)

#define LOG_WARN0(...)                                                    \
  do {                                                                     \
    auto x = yychi::LogHelper(yychi::LogLevel::WARN, __FILE__, __LINE__); \
    if (x.CheckLevel()) {                                                  \
      x(__VA_ARGS__);                                                      \
    }                                                                      \
  } while (0)

#define LOG_ERROR0(...)                                                    \
  do {                                                                     \
    auto x = yychi::LogHelper(yychi::LogLevel::ERROR, __FILE__, __LINE__); \
    if (x.CheckLevel()) {                                                  \
      x(__VA_ARGS__);                                                      \
    }                                                                      \
  } while (0)

// We do not nedd LOG_FATAL0 since FATAL is always logged out.
