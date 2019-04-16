#include <iostream>
#include <queue>

using namespace std;

queue<int> pile;

void solution(int n) {
    // initialize queue
    for (int i=0; i != n; ++i)
        pile.push(i + 1);
    
    while (!pile.empty()) {
        cout << pile.front() << ' ';
        pile.pop();
        pile.push(pile.front());
        pile.pop();
    }
}

int main() {
    int num_test = 0;
    int n = 0;
    cin >> num_test;
    
    while (num_test--){
        cin >> n;
        solution(n);
        cout << '\n';
    }
    return 0;
}
