#include <stack>
#include <string>
#include <iostream>

using std::stack;
using std::string;

// print the stack from bottom
void printer(stack<string>& s) {
    stack<string> seq;
    while (!s.empty()) {
        seq.push(s.top());
        s.pop();
    }
    while (!seq.empty()) {
        std::cout << seq.top();
        seq.pop();
    }
}

int main() {
    string setence("This is (uyf (ihcyy) tneduts), and he loves (nnykuy).");
    stack<string> expr;
    bool close = false;
    for (const auto &e : setence) {
        expr.push(string(1, e));

        if (e == ')') close = true;
        if (close) { // eval the expr
            expr.pop(); // pop the `)`
            string val;
            while (expr.top() != "(") {
                val += expr.top();
                expr.pop();
            }
            expr.pop(); // pop the corresponding `(`
            expr.push(val); // push the value of the expr
            close = false;
        }
    }
    printer(expr);
    return 0;
}
