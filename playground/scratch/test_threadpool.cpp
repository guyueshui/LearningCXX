
#include "macros.h"
#include "simple_log.h"
#include "thread_pool.h"
#include "vczh_test.h"
#include <sstream>
#include <thread>


using namespace std;
using utils::ThreadPool, utils::ThreadPoolIndexed;

int main() {
    yychi::Logger::Inst().Shutdown();
    return 0;
}

TEST_CASE(ThreadPool) {
    ThreadPool pool(5);
    int n = 10;
    while (n--) {
        pool.Post([]{
            ostringstream os;
            os << "i am run on " << this_thread::get_id() << '\n';
            cout << os.str();
        });
    }
    this_thread::sleep_for(1s);
}

TEST_CASE(ThreadPooli) {
    ThreadPoolIndexed t;
    TEST_ASSERT(t.Start(5));
    for (int i = 0; i < 10; ++i) {
        t.Post(i, [](int x){
            ostringstream os;
            os << x << " am run on " << this_thread::get_id() << '\n';
            cout << os.str();
        });
    }
    this_thread::sleep_for(1s);
    t.Stop();
    t.Stop();
}