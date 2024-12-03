#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;

/**
 * 考虑竖式乘法中，单个位置上的结果累加，考虑循环进位。
 */
void add_by_carrier(string& o, size_t index, int value)
{
    if (value <= 0 || index >= o.size()) return;
    int p = value + (o[index] - '0');
    o[index] = '0' + (p % 10);
    add_by_carrier(o, index+1, p/10);
}

string multiply(string num1, string num2)
{
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    string ret(num1.size() + num2.size(), '0');

    for (size_t i = 0; i < num1.size(); ++i)
    {
        int p1 = num1[i] - '0';
        for (size_t j = 0; j < num2.size(); ++j)
        {
            add_by_carrier(ret, i+j, p1 * (num2[j] - '0'));
        }
    }
    while (ret.size() > 1 && ret.back() == '0')
        ret.pop_back();

    std::reverse(ret.begin(), ret.end());
    return ret;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
        return -1;

    printf("args: %s, %s, %s\n", argv[0], argv[1], argv[2]);

    string n1 {argv[1]};
    string n2 {argv[2]};

    cout << n1 << " * " << n2 << " = "; 
    cout << multiply(n1, n2) << endl;
    return 0;
}
