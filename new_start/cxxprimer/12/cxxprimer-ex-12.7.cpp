#include <memory>
#include <vector>
#include <iostream>

using namespace std;

shared_ptr<vector<int>> fun1()  {
    return make_shared<vector<int>>();
}

void fun2(vector<int>& v) {
    int tmp;
    while (cin >> tmp)
        v.push_back(tmp);
}

void fun3(vector<int>& v) {
    for (auto e : v)
        cout << e << ' ';
}

// test
int main() {
    auto p = fun1();
    fun2(*p);
    fun3(*p);
    return 0;
}
