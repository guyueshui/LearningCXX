/** @DESCRIPTION
 *	Write a program that takes an arithmetical expression in RPN and returns
 *	the number that the expression evaluates to.
 *
 *	For more detail: see EPI p.132
 */

#include <stack>
#include <string>
#include <iostream>
#include <sstream>

using std::stack;
using std::string;

class Solution {
public:
    // use stack to record partial results
    int Eval1(const string& RPN_expression) {
        size_t pos0 = 0, pos1 = 0;
        stack<string> stk;
        // iteratively processing
        while (pos1 != string::npos) {
            pos1 = RPN_expression.find(',', pos0);
            stk.push(RPN_expression.substr(pos0, pos1 - pos0));
            // if it forms a sub expression, evaluate it
            if (stk.top() == "+" || stk.top() == "-"
            ||  stk.top() == "*" || stk.top() == "/")
                sub_eval(stk);
            pos0 = pos1 + 1;
        }
        return std::stoi(stk.top());
    }

    // epi solution
    int Eval(const string& RPN_expression) {
        stack<int> intermidiate_results;
        std::stringstream ss(RPN_expression);
        string token;
        const char kDelimiter = ',';

        while (std::getline(ss, token, kDelimiter)) {
            if (token == "+" || token == "-"
            ||  token == "*" || token == "/") {
                const int y = intermidiate_results.top();
                intermidiate_results.pop();
                const int x = intermidiate_results.top();
                intermidiate_results.pop();
                switch (token.front()) { // convert string to char
                    case '+':
                        intermidiate_results.emplace(x + y);
                        break;
                    case '-':
                        intermidiate_results.emplace(x - y);
                        break;
                    case '*':
                        intermidiate_results.emplace(x * y);
                        break;
                    case '/':
                        intermidiate_results.emplace(x / y);
                        break;
                }
            } else { // token is a number
                intermidiate_results.emplace(std::stoi(token));
            }
        }
        return intermidiate_results.top();
    }
private:
    // eval the sub-expression and push the value to the stack 
    void sub_eval(stack<string>& s) {
        string op = s.top();
        s.pop();
        int val2 = std::stoi(s.top());
        s.pop();
        int val1 = std::stoi(s.top());
        s.pop(); // now s should be empty
        int ret;
        if (op == "+")
            ret = val1 + val2;
        else if (op == "-")
            ret = val1 - val2;
        else if (op == "*")
            ret = val1 * val2;
        else if (op == "/")
            ret = val1 / val2;
        else
            throw "bad operator!";
        s.push(std::to_string(ret));
    }
};


// test
int main(int argc, char *argv[]) {
    string exp("3,4,+,2,*,1,+");
    std::cout << Solution().Eval(exp);
    return 0;
}
