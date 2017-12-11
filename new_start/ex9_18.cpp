#include <iostream>
#include <cstring>
#include <deque>
#include <list>

using namespace std;

/*int main(int argc, char const *argv[]) {
    string word;
    deque<string> sdeque;
    cout << "please input some string: \n";
    while (cin>>word) {
        sdeque.push_back(word);
    }

    for (auto elem : sdeque)
        cout << elem << ' ';

    return 0;
}*/

int main(int argc, char const *argv[]) { //用list写
    string word;
    list<string> slst;

    cout << "please input some string: \n";
    while (cin>>word)
        slst.push_back(word);

    for (auto elem : slst)
        cout << elem << ' ';
    
    return 0;
}
