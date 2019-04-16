#include "../Sales_data.ipp"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    Sales_data total;
    ifstream input(argv[1]); // open file

    if (read(input, total)) {
        Sales_data trans;
        while (read(input, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                // write to cout
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    } else 
        cerr << "No data?!" << endl;

    return 0;
}
