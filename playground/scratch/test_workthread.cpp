#include "simple_log.h"
#include "vczh_test.h"
#include "utils.h"
#include <atomic>
#include <thread>

using yychi::Logger;
using yychi::LogLevel;
using namespace std;

int main() {
    Logger::Inst().Shutdown();
    return 0;
}


struct Demo : public utils::WorkThreadT<int> {
    typedef utils::WorkThreadT<int> Base;

    bool OnThreadInitialize(const char* name) override {
        SetTimerInterval(50);
        return Base::OnThreadInitialize("demo_work");
    }

    void OnTimer() override {
        LOG_INFO("i = %zu", i++);
    }

    size_t i = 0;
};

TEST_CASE(thread_timer) {
    Demo d;
    d.Start();
    while (d.i < 10) { // read only
        this_thread::yield();
    }
    TEST_ASSERT(d.i == 10);
    d.Stop();
}