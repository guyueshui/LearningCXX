/** @Description
 *  Given a string containing a set of words separated by whitespace, we would like
 *  to transform it to a string in which the words appear in the reverse order. For
 *  example, "Alice likes Bob" transforms to "Bob likes Alice". We do not need to
 *  keep the original string.
 *
 *  Implement a function for reveresing the words in s.
 */

#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

using std::string;

class Solution {
public:
    // use a stack to store each word, then reverse
    void ReverseWords1(string& s) {
        std::stack<string> stk;
        size_t pos0 = 0, pos1 = 0;
        while ((pos1 = s.find(' ', pos0)) != string::npos) {
            stk.push(s.substr(pos0, pos1 - pos0));
            pos0 = pos1 + 1;
        }
        stk.push(s.substr(pos0)); // add the last word
        // modify s
        s.clear();
        while (!stk.empty()) {
            s += stk.top();
            s += " ";
            stk.pop();
        }
        s.pop_back(); // remove last whitespace
    }

    // first reverse the whole string, then each word
    void ReverseWords2(string& s) {
        std::reverse(s.begin(), s.end());
        size_t pos0 = 0, pos1 = 0;
        while ((pos1 = s.find(' ', pos0)) != string::npos) {
            std::reverse(s.begin() + pos0, s.begin() + pos1);
            pos0 = pos1 + 1;
        }
        std::reverse(s.begin() + pos0, s.end());
    }

    // epi solution
    void ReverseWords(string* s) {
        // Reverse the whole string first.
        std::reverse(s->begin(), s->end());

        size_t start = 0, end;
        while ((end = s->find(' ', start)) != string::npos) {
            // Reverse each word in the string.
            std::reverse(s->begin() + start, s->begin() + end);
            start = end + 1;
        }
        // Reverse the last word.
        std::reverse(s->begin() + start, s->end());
    }
};

// test
int main() {
    string sentence("Cool? Am I");
    Solution().ReverseWords(&sentence);
    std::cout << sentence;
    return 0;
}
