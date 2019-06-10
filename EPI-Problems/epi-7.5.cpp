/** @Decription
 *  For the purpose of this problem, define a palindromic string to be a string
 *  which when all the nonalphanumeric are removed it reads the same front to
 *  back ignoring case. For example, "A man, a plan, a canal, Panama." and
 *  "Able was I, ere I saw Elba!" are palindromic, but "Ray a Ray" is not.
 *
 *  Implement a function which takes as input a string s and returns true if s
 *  is a palindromic string.
 */

#include <string>
#include <iostream>
#include <algorithm>

using std::string;

class Solution {
public:
    // naive solution: need extra space
    bool IsPalindrome1(const string& s) {
        string compact_str;
        for (auto e : s) {
            if (std::isalnum(e)) // if the char is alphabetic or numeric
                compact_str.push_back(e);
        }
        // get a reverse
        string rev_str;
        for (auto i = compact_str.rbegin(); i != compact_str.rend(); ++i)
            rev_str.push_back(*i);
        return compact_str == rev_str;
    }

    // better one
    bool better_IsPalindrome(const string& s) {
        for (auto beg = s.cbegin(), end = s.cend(); end >= beg;) {
            if (std::isalnum(*beg) && std::isalnum(*(end-1))) {
                // case-insensitive comparison
                if (std::tolower(*beg) != std::tolower(*(end-1)))
                    return false;
                ++beg, --end;
            } else if (!std::isalnum(*beg)) 
                ++beg;
            else // !std::isalnum(*(end-1))
               --end; 
        }
        return true;
    }

    // epi solution
    bool IsPalindrome(const string& s) {
        // i moves forward, and j moves backward
        int i = 0, j = s.size() - 1;
        while (i < j) {
            // i and j both skip non-alphanumeric characters
            while (!std::isalnum(s[i]) && i < j)
                ++i;
            while (!std::isalnum(s[j]) && i < j)
                --j;
            if (std::tolower(s[i++]) != std::tolower(s[j--]))
                return false;
        }
        return true;
    }
};

// test
int main() {
    string s("A man, a plan, a canal, Panama.");
    std::cout << Solution().IsPalindrome(s);
    return 0;
}
