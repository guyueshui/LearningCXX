#include <string>
#include <iostream>

using namespace std;

void fun1(const string& s) {
    string numbers("0123456789");
    for (size_t pos = 0; 
            (pos = s.find_first_of(numbers, pos)) != string::npos;
            ++pos) {
        cout << "(pos, num): ("
            << pos << ", "
            << s[pos] << ")\n";
    }
    string letters("abcdefghijklmnopqrstuvwxyz \
            ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    for (size_t pos = 0; 
            (pos = s.find_first_of(letters, pos)) != string::npos;
            ++pos) {
        cout << "(pos, letter): ("
            << pos << ", "
            << s[pos] << ")\n";
    }
}

void fun2(const string& s) {
    string numbers("0123456789");
    string letters("abcdefghijklmnopqrstuvwxyz \
            ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    for (size_t pos = 0; 
            (pos = s.find_first_not_of(letters, pos)) != string::npos;
            ++pos) {
        cout << "(pos, num): ("
            << pos << ", "
            << s[pos] << ")\n";
    }
    for (size_t pos = 0; 
            (pos = s.find_first_not_of(numbers, pos)) != string::npos;
            ++pos) {
        cout << "(pos, letter): ("
            << pos << ", "
            << s[pos] << ")\n";
    }
}

int main() {
    string str("ab2c3d7R4E6");
    string letters("abcdefghijklmnopqrstuvwxyz \
            ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    fun1(str);
    cout << "\n-----------\n";
    fun2(str);
    return 0;
}
