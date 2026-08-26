#include "macros.h"
#include "simple_log.h"
#include "test_utils.h"
#include "utils.h"
#include "vczh_test.h"
#include <chrono>
#include <thread>


using namespace std;
using yychi::LogLevel;
using yychi::Logger;


int main() {
    // make pending logs be flushed.
    yychi::Logger::Inst().Shutdown();
    return 0;
}


TEST_CASE(early) {
    yychi::LoggerImpl logger;
    // logger.AddConsoleSink();
    logger.AddFileSink("early.log");
    logger.AddRotateFileSink("log/rot.log", 0, 10*1024, 3);
    logger.SetLogLevel(LogLevel::TRACE);
    logger.Log(LogLevel::FATAL, __FILE__, __LINE__, "are you fatal");
    logger.Log(LogLevel::ERROR, __FILE__, __LINE__, "are you error");
    logger.Log(LogLevel::WARN, __FILE__, __LINE__, "are you warn");
    logger.Log(LogLevel::INFO, __FILE__, __LINE__, "are you info");
    logger.Log(LogLevel::DEBUG, __FILE__, __LINE__, "are you debug");
    logger.Log(LogLevel::TRACE, __FILE__, __LINE__, "are you trace");
    logger.LogInfo(__FILE__, __LINE__, "hi are you ok, test direct from LogInfo a=%d, c=%c", 1, 'b');
    logger.LogWarn(__FILE__, __LINE__, "are you ok, i am from LogWarn");
    logger.LogWarn(__FILE__, __LINE__, "let me make some %s, format %d", "str", 5);
    constexpr int N = 10000;
    // constexpr int N = 0;
    unsigned long long cost = 0;
    utils::TimeCounter t;
    for (int i = 0; i < N; ++i) {
        t.reset();
        logger.LogInfo(__FILE__, __LINE__, "this is aksdjflasjdkfjasldkjflkjaslkdjfaksjdkfjasd %d", i);
        cost += t.elapsed<chrono::microseconds>();
        // this_thread::sleep_for(100ms);
    }
    printf("log %d times cost avg %.2fus\n", N, 1.0 * cost / N);
    // this_thread::sleep_for(3s);
}

TEST_CASE(logger_manager) {
    auto& l = Logger::Inst().GetLogger("test");
    l.AddFileSink("log_manager.log");
    l.LogWarn(__FILE__, __LINE__, "this will be logged to console.");
    l.RemoveSink(yychi::SinkSlot::CONSOLE); // remove 之前的 log，在实际写入时可能已经没有这个 sink，造成冲突
    l.LogWarn(__FILE__, __LINE__, "this will not.");

    l.LogDebug(__FILE__, __LINE__, "this will be logged.");
    l.SetLogLevel(LogLevel::INFO);
    l.LogDebug(__FILE__, __LINE__, "this will not. %d", 99);
}

int foo(const char* tag) {
    PRINT_FUNC(tag);
    return 2333;
}

TEST_CASE(default_logger) {
    LOG_TRACE("default_logger: are you trace");
    LOG_DEBUG("a=%d, c=%c, haha", 1, 'a');
    LOG_ERROR("a=%d, c=%c, %s", 1, 'a', "this is a error log");
    LOG_FATAL("test fatal");
    LOG_FATAL("fmt some thing %d", 99);

    Logger::Inst().GetLogger("default").SetLogLevel(LogLevel::INFO);
    LOG_ERROR("haha");
    LOG_ERROR0("a=%d, b=%c", foo("error0"), 'a');
    LOG_ERROR("a=%d, b=%c", foo("error"), 'a');
    LOG_DEBUG0("a=%d, b=%c", foo("debug0"), 'b');
    LOG_DEBUG("a=%d, b=%c", foo("debug"), 'b');

    string_view s{"hello world"};
    LOG_FATAL("this is %s", s.data());
    s.remove_suffix(6);
    cout << s << endl;
    LOG_FATAL("after remove suffix: %s", s.data());
    LOG_FATAL("use this way %*s", s.size(), s.data());
    LOG_FATAL("use this way %.*s", s.size(), s.data());
}