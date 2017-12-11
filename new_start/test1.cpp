#include <iostream>
#include <array>

using namespace std;

int main(int argc, char const *argv[]) {
    array<int,10> a1 = {0,1,2,3,4,5,6,7,8,9};
    array<int,10> a2 = {0};
    a1 = a2;
    a2 = {0,1,2,3,4};
    cout<< a2[2] << endl;
    return 0;
}
