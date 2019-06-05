/**
 *  @Description:
 *  Write a program which takes ana integer and returns the integer corresponding
 *  to the digits of the input written in reverse order. For example, the reverse
 *  of 42 is 24, and the reverse of -314 is -413.
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    // @brute_force
    static int reverse(int n) {
        // address the sign
        bool sign = false;
        if (n < 0) {
            sign = true;
            n = -n;
        }
        string s = std::to_string(n);
        // reverse string
        string tmp;
        for (auto i = s.rbegin(); i != s.rend(); ++i)
            tmp += *i;
        // convert to int
        int ret = std::stoi(tmp);
        return sign? -ret : ret;
    }

    // better one
    static int better_reverse(int n) {
        bool sign = false;
        if (n < 0) {
            sign = true;
            n = -n;
        }
        // iteratively modulo
        int ret = iter(n, 0, 0);
        return sign? -ret : ret; 

    }

    // epi solution
    long Reverse(int x) {
        long result = 0, x_remaining = abs(x);
        while (x_remaining) {
            result = result * 10 + x_remaining % 10;
            x_remaining /= 10;
        }
        return x < 0 ? -result : result;
    }

private:
    /** @idea
     *  Suppose n = 12345, each time I take
     *      q = n / 10
     *      r = n % 10
     *  See how it works:
     *      q1 = 1234
     *      r1 = 5
     *      ---
     *      q2 = 123
     *      r2 = 4
     *      ---> r1 * 10 + r2 = 54
     *      q3 = 12
     *      r3 = 3
     *      ---> 54 * 10 + r3 = 543
     *      ...
     *      you got it!
     */
    static int iter(int _q, int _r, int _ret) {
        if (_q == 0)
            return _ret * 10 + _r;
        else // tail recursion
            return iter(_q / 10, 
                        _q % 10,
                        _ret * 10 + _r);
    }
};

// test
int main() {
    cout << Solution::reverse(-1234567);
    cout << endl << Solution::better_reverse(-1234567);
    return 0;
}
