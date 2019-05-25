#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main(int argc, char const *argv[]) {
    list<int> ilst{0,1,2,3,4,5,6,7,8,9};
    deque<int> odd,even;

    for (auto i=ilst.begin(); i != ilst.end(); ++i) { //std::list::iterator i
        if ((*i) & 1) { //if (*i) is a odd
            odd.push_back(*i);
        } else {
            even.push_back(*i);
        }
    }

    for (auto i : odd) cout << i << ' ';
    cout << endl;
    for (auto i : even) cout << i << ' ';

    return 0;
}
