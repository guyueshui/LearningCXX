/** 
 *  Hellobike 2019 interview.
 */
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string itob36(int n) {
        int r = 0; // remainder of n mod 36
        string tmp;
        // iteratively divde by 36 to get each digit
        while (n) {
            r = n % 36;
            tmp += MAP[r];
            n /= 36;
        }
        // reverse tmp to ret
        string ret;
        cout << "tmp is " << tmp << endl;
        for (auto iter = tmp.rbegin(); iter != tmp.rend(); ++iter)
            ret.push_back(*iter);
        return ret;
    }
private:
    string MAP[36] = {"0", "1", "2", "3", "4", "5",     \
                      "6", "7", "8", "9", "A", "B",     \
                      "C", "D", "E", "F", "G", "H",     \
                      "I", "J", "K", "L", "M", "N",     \
                      "O", "P", "Q", "R", "S", "T",     \
                      "U", "V", "W", "X", "Y", "Z"};
};

// test
int main() {
  int number = 12345;
  cout << Solution().itob36(number);
  return 0;
}
