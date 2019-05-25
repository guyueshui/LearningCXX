#include <vector>
#include <iostream>

using std::vector;

int main() {
    vector<int> v1{1,2,3};
    vector<int> v2;
    auto printer = [](int x) {std::cout << x << std::endl;};
    printer(v1[0]);
    printer(v1.front());
    printer(v1.at(0));
    printer(*v1.begin());
    std::cout << "--------\n";
    printer(v2.at(0)); // throw exception
    printer(v2[0]);
    printer(v2.front());
    printer(*v2.begin());
    return 0;
}
