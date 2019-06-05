/** @Description
 *  Write a program which takes as input an array of digits encoding a decimal
 *  number D and updates the array to represent the number D+1. For example,
 *  if the input is <1,2,9> then you should update the array to <1,3,0>. Your
 *  algorithm should work even if it is implemented in a language that has
 *  finite-precision arithmetic.
 */

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    /** @idea
     *  Just like how we add two numbers in school. If there is a carrier,
     *  propogate it, if no, add the digit by 1 and we are done.
     */
    static vector<int>& PlusOne1(vector<int>& arr) {
        int carrier = 1, cur_sum = 0;
        for (auto i = arr.rbegin(); i != arr.rend(); ++i) {
            cur_sum = *i + carrier;
            if (cur_sum > 9) {
                *i = cur_sum % 10;
                carrier = 1;
            } else {
                *i = cur_sum;
                carrier = 0;
                break;
            }
        }
        if (carrier) // if there is a carrier-out at highest digit
            arr.insert(arr.begin(), 1);
        
        return arr;
    }

    // epi solution
    static vector<int> PlusOne(vector<int> A) {
        ++A.back();
        for (int i = A.size() - 1; i > 0 && A[i] == 10; --i) {
            A[i] = 0, ++A[i - 1];
        }
        if (A[0] == 10) {
            // Need additional digit as the most significant digit (i.e., A[0])
            // has a carry-out.
            A[0] = 0;
            A.insert(A.begin(), 1);
        }
        return A;
    }
};

namespace Variant {
    /** @Description
     *  Write a program which takes as input two strings s and t of bits
     *  encoding binary numbers Bs and Bt, respectively, and returns a
     *  new string of bits representing the number Bs+Bt.
     */

    // sum two chars
    int sum_char(char c1, char c2) {
        return std::stoi(string() + c1) 
            + std::stoi(string() + c2);
    }
    // sum char with int
    int sum_ci(char c, int i) {
        return std::stoi(string() + c) + i;
    }
    // convert int to char
    char itoc(int i) {
        if (i == 0) return '0';
        if (i == 1) return '1';
        else throw "I can't convert this number";
    }

    string BinaryPlus(string s, string t) {
        // which is longer?
        string ret;
        if (s.size() < t.size()) {
            ret = t;
            t = s;
        } else ret = s;
        std::cout << ret << ' ' << t << std::endl;
        // useful variables
        int carrier = 0, cur_sum = 0;
        auto ret_id = ret.rbegin(),
             t_id = t.rbegin();
        // add ret with t
        while (t_id != t.rend()) {
            cur_sum = sum_char(*t_id, *ret_id) + carrier;
            if (cur_sum >= 2) {
                carrier = 1;
                *ret_id = itoc(cur_sum % 2);
            } else {
                carrier = 0;
                *ret_id = itoc(cur_sum);
            }
            ++t_id, ++ret_id;
        }
        // add ret with carrier if have
        while (carrier && ret_id != ret.rend()) {
            cur_sum = sum_ci(*ret_id, carrier);
            if (cur_sum >= 2) {
                carrier = 1;
                *ret_id = itoc(cur_sum % 2);
            } else {
                carrier = 0;
                *ret_id = itoc(cur_sum);
                break;
            }
            ++ret_id;
        }
        if (carrier) // if there is a carry-out at highest digit
            ret.insert(ret.begin(), '1');
        return ret;
    }
}

// test
int main() {
    vector<int> D = {1,3,4,1,4,9,6,9,9};
    auto printer = [](const vector<int>& v) {
        for (auto e : v) std::cout << e;
        };

    printer(D);
    std::cout << " + 1 = ";
    printer(Solution::PlusOne(D));
    std::cout << std::endl
        << Variant::BinaryPlus("11111", "1110");
    return 0;
}
