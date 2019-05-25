#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

int sum(const vector<string>& v) {
    int ret = 0;
    for (auto &e : v) {
        ret += std::stoi(e);
    }
    return ret;
}

float sum_f(const vector<string>& v) {
    float ret = 0.0; 
    for (auto &e : v)
        ret += std::stof(e);
    return ret;
}

// test
int main() {
    vector<string> seq = {"12","323","1234"};
    vector<string> seq_f = {"3.1415", "45.15", "12.511", "1.1"};
    std::cout << sum(seq) << std::endl
        << sum_f(seq_f) << std::endl;
    return 0;
}
