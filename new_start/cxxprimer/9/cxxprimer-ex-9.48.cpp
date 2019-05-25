#include <string>
#include <iostream>

using namespace std;

int main() {
    string name("AnnaBelle");
    string numbers("0123456789");
    cout << numbers.find(name) << endl; // 18446744073709551615
    // as you see, it returns string::npos
    return 0;
}
