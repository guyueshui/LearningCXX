#include <iostream>
#include <istream>

using namespace std;

istream& rw(istream& istrm) {
    auto old_state = istrm.rdstate();
    istrm.clear(); // ready to use
    char e;
    while (istrm >> e) {
        cout << e;
    }
    istrm.setstate(old_state);
    return istrm;
}
