// #include<stdio.h>
// 
// void fun(char* t, char* s) {
//     while (*t != '\0')
//         t++;
//     while ((*t++=*s++) != '\0');
// }
// 
// int main() {
//     char s1[10] = "123", s2[10] = "9978";
//     fun(s1, s2);
//     printf(s1);
//     return 0;
// }

#include<string>
#include<vector>
#include<iostream>
#include<cmath>

using namespace std;

class Solution {};

int numSee(const vector<int>& soldierArray, int numSoldier) {
    if (numSoldier == 0) return 0;
    int curMax = soldierArray[0];
    int cnt = 1;
    for (int i=1; i<numSoldier; ++i) {
        if (soldierArray[i] > curMax) {
            curMax = soldierArray[i];
            ++cnt;
        }
    }
    return cnt;
}

void f(double n) {
    cout << "==>" << n << endl;
}
// entrance
int main(){
    /*
    int numCols;
    vector<int> soldierArray;
    vector<int> res;
    cout << "input numCols: \n";
    cin >> numCols;
    for (int i=0; i!=numCols; ++i) {
        int tmp = 0;
        int numSoldier = 0;
        cout << "input numSoldier: \n";
        cin >> numSoldier;
        while (cin >> tmp) {
            soldierArray.push_back(tmp);
        }
        res.push_back(numSee(soldierArray, numSoldier));
    }

    for (auto &c : res) {
        cout << c << endl;
    }
    */
    double a = pow(2, 3);
    f(a);
    return 0;
}
