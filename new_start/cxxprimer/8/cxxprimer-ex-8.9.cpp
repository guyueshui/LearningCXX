#include <sstream>
#include <iostream>

using namespace std;

istringstream& rw(istringstream& istrm) {
    auto old_state = istrm.rdstate();
    // reset iostate will not affect 
    // the contents of a stream
    istrm.clear();
    string e;
    while (istrm >> e)
        std::cout << e << endl;

    istrm.setstate(old_state);
    return istrm;
}

int main() {
    istringstream is("you can do it!");
    rw(is);
    return 0;
}
