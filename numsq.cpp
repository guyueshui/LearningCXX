#include<iostream>

using namespace std;

int solver(int i, int j) {
    if(i == j) return i+1;
    else if (i < j) {
        if (i+1 == j) {
            return 2*(i+1);
        } else {
            return i+1 + solver(i, j-1);
        }
    } else {
        if (j+1 == i) {
            return 2*(j+1);
        } else {
            return j+1 + solver(i-1, j);
        }
    }
}

int main(){
    int i = 0, j = 0;
    cin >> i >> j;
    cout << solver(i, j);
}
