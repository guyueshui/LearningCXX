#include <iostream>
#include <vector>

using std::vector;

vector<int>* fun1() {
    return new vector<int>;
}

void fun2(vector<int>& v) {
    int tmp = 0;
    while (std::cin >> tmp)
        v.push_back(tmp);
}

void fun3(vector<int>& v) {
    for (auto e : v)
        std::cout << e << ' ';
}

// test
int main() {
    auto p = fun1();
    fun2(*p);
    fun3(*p);
    delete p; // release memory
    return 0;
}
