#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Pos {
public:
    int x;
    int y;
};

class Mat {
public:
    vector<Pos> ones;
    vector<Pos> twos;
    vector<vector<int> > table;

    void read_input() {
        int var;
        while (cin >> var) {
            table.push_back(vector<int>());
        }
    }

    int steps(int i, int j) {
        int d_border = table.size() - 1;
        int r_border = table[0].size() - 1;

        for (auto iter = twos.begin();
                iter != twos.end(); 
                ++iter) {
            int i = iter -> x,
               j = iter -> y;
            build_IJ
             
        }
    }

    void printer() {
        for (auto &r : table) {
            for (auto &c : r)
                cout << c << ' ';
            cout << endl;
        }
    }
};

int main() {
    Mat m;
    m.read_input();
    return 0;
}
