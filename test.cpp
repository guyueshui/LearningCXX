#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main(){
    string a = "1";
    std::reverse(a.begin(), a.end());
    cout << a;
	return 0;
}
