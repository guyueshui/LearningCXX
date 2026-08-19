#include "macros.h"
#include "vczh_test.h"
#include "utils.h"
#include <algorithm>
#include <atomic>
#include <cstring>
#include <exception>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>
 
int main() { return 0; }
using std::cout, std::endl;
 
TEST_CASE(foo) {
    std::cout << "running test ...\n";
    TEST_ASSERT(1==2);
    std::cout << "running end ...\n";
    std::vector<int> v;
    v.max_size();
    v.capacity();
    v.push_back(1);
    int a = 1;
    v.push_back(a);
}

TEST_CASE(bar) {
    char buf[] = {'a', 'b', 'c'};
    cout << buf << endl;

    {
        // overflow test
        uint32_t x = UINT32_MAX + 2;
        cout << "UINT32_MAX + 2 = " << x << endl; // outputs 1
    }

    TEST_ASSERT(1==true);
    std::cout << "ok!\n";
    std::priority_queue<std::pair<int, int>> max_heap;
    max_heap.push({1, 2});
    std::pair<int,int> a = {3, 4};
    max_heap.push(a);
    auto x = max_heap.top();
    max_heap.pop();
    max_heap.emplace(5,6);
    auto another = max_heap;
    auto z = std::move(max_heap);
    printf("zl=%lu, max_heap_len=%lu\n", z.size(), max_heap.size());
    std::vector<int> b{1,2,3};
    std::push_heap(b.begin(), b.end(), [](int a, int b){return a < b;});
    std::sort_heap(b.begin(), b.end());
    PLACEHOLDER;
    cout << (2 - 3) % 7 << endl;
}

TEST_CASE(scanf) {
    const char* str = "2026-07-01 09:30:12";
    int h, m, s;
    auto x = sscanf(str, "%d:%d:%d", &h, &m, &s);
    printf("x=%d ~ %d:%d:%d\n", x, h, m, s);
    TEST_ASSERT(x == 3);
}

TEST_CASE(rand_str) {
    int len = 20;
    char* str = new char[len + 1];
    printf("%s\n", utils::rand_str(str, len));
    delete[] str;
}

TEST_CASE(array) {
    int arr[6]={1,2,3,4,5,6};
    // int &refs[6]=arr;
    int (&arrRef)[6]=arr;
    int (*parry)[6]=&arr;
    // int (*parry1)[6]=arr;
    for(size_t i=0;i<6;++i){
        cout<<(*parry)[i]<<" ";
    }
    cout<<endl;
    cout<<"parry:"<<parry<<endl;
    cout<<"*parry:"<<*parry<<endl;
    cout<<"arr:"<<arr<<endl;
    cout<<"arrRef:"<<arrRef<<endl;
    cout<<"++parry:"<<++parry<<endl;
    cout<<"*(++parry):"<<*(++parry)<<endl;
    cout<<"**(++parry):"<<**(++parry)<<endl;
    cout<<"**parry"<<**parry<<endl;
    
    cout<<"*(*parry+1):"<<*(*parry+1)<<endl;
    // cout<<"*(++arr):"<<*(++(int*(arr)))<<endl;
    cout<<"arr:"<<arr<<endl;
}

TEST_CASE(cout_interrupt) {
    return;
    using namespace std;
    atomic_bool stop = false;
    std::thread t1([&]{
        while (!stop) {
            cout << 1 << 2 << 3 << '\n';
        }
    });
    std::thread t2([&]{
        while (!stop) {
            cout << 4 << 5 << 6 << '\n';
        }
    });
    std::this_thread::sleep_for(3s);
    stop.store(true, std::memory_order_release);
    t1.join();
    t2.join();
}

struct A : private utils::NonCopyable {
    A() = default;
    // A(A&&) {}
};

TEST_CASE(noncopyable) {
    A a;
    // A b = std::move(a);
}

 
struct Good: std::enable_shared_from_this<Good> // 注意：继承
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
 
struct Bad
{
    // 错误写法：用不安全的表达式试图获得 this 的 shared_ptr 对象
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};
 
TEST_CASE(shared_from_this) {

    // 正确的示例：两个 shared_ptr 对象将会共享同一对象
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
 
    // 错误的使用示例：调用 shared_from_this 但其没有被 std::shared_ptr 占有
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // C++17 前为未定义行为；C++17 起抛出 std::bad_weak_ptr 异常
        std::cout << e.what() << '\n';    
    }
 
    try {
        // 错误的示例，每个 shared_ptr 都认为自己是对象仅有的所有者
        std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
        std::shared_ptr<Bad> bp2 = bp1->getptr();
        std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
        // UB：Bad 对象将会被删除两次
    } catch (std::exception& e) {
        cout << e.what() << '\n';
    } catch (...) {
        cout << "unknown exception\n";
    }
} 