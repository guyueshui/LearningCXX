#include "simple_log.h"
#include "test_utils.h"
#include "vczh_test.h"
#include <thread>

int main() { return 0; }

using namespace std;
using Logger = yychi::SimpleLogger;
using yychi::LogLevel;

TEST_CASE(early) {
    Logger logger;
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
    for (int i = 0; i < N; ++i) {
        logger.LogInfo(__FILE__, __LINE__, "this is aksdjflasjdkfjasldkjflkjaslkdjfaksjdkfjasd %d", i);
        // this_thread::sleep_for(100ms);
    }
    // this_thread::sleep_for(3s);
}

TEST_CASE(default_logger) {
    LOG_TRACE("default_logger: are you trace");
    LOG_DEBUG("a=%d, c=%c, haha", 1, 'a');
    LOG_ERROR("a=%d, c=%c, %s", 1, 'a', "this is a error log");
}