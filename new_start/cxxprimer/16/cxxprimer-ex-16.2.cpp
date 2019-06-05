#include <iostream>
#include <string>

using std::cout;
using std::endl;

// a function template for compare two things
template <typename T>
bool compare(const T& a, const T& b) { return a < b; }

int main() {
    int a = 3, b = 4;
    cout << "compare int: " << compare(a, b) << endl;

    double c = 3.3, d = 2.2;
    cout << "compare double: "
        << compare(c, d) << endl;

    std::string e = "haha", f = "hah";
    cout << "compare string: "
        << compare(e, f) << endl;
    return 0;
}
