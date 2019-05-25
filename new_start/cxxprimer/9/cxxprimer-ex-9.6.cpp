#include <list>

using std::list;

int main() {
    list<int> lst1;
    list<int>::iterator iter1 = lst1.begin(),
                        iter2 = lst1.end();
    
    /*
     * The iterator of list isn't comparable since
     * it is not a sequential structure.
     */
    // while (iter1 < iter2) {
    while (iter1 != iter2) {
        ++iter1;
    }
}
