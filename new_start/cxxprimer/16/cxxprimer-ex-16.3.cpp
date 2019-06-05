#include "../Sales_data.ipp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

// a function template for compare two things
template <typename T>
bool compare(const T& a, const T& b) { return a < b; }

int main() {
    Sales_data book1("Qt: From instroduction to given up"),
               book2("C++ Primer 5th ed.");
    cout << "compare Sales_data: "
        << compare(book1, book2) << endl;
    return 0;
}

/*
 * The g++ complains:
 * cxxprimer-ex-16.3.cpp: In instantiation of ‘bool compare(const T&, const T&) [with T = Sales_data]’:
 * cxxprimer-ex-16.3.cpp:17:32:   required from here
 * cxxprimer-ex-16.3.cpp:11:49: 错误：no match for ‘operator<’ (operand types are ‘const Sales_data’ and ‘const Sales_data’)
 *  bool compare(const T& a, const T& b) { return a < b; }
 *                                                 ~~^~~
 */
