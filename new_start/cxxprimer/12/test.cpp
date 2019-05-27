#include "StrBlob.hpp"
#include <iostream>

using namespace std;

int main() {
    StrBlob svec({"i", "love", "you"});
    StrBlob a;
    cout << svec.front();
    cout << a.back();
    return 0;
}
