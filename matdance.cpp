#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Pos {
public:
    int x;
    int y;
    Pos(int _x, int _y) : x(_x), y(_y) {}
};

class Mat {
public:
    vector<Pos> ones; // track ones
    vector<Pos> twos; // track twos
    vector<vector<int> > table;

    // build the table from input
    void read_input() {
        string line, word;

        for (int i = 0; getline(cin ,line); ++i) {
            istringstream record(line);
            vector<int> row;

            for (int j = 0; record >> word; ++j) {
                int num = std::stoi(word);
                row.push_back(num);

                if (num == 1)
                    ones.push_back(Pos(i, j));
                else if (num == 2)
                    twos.push_back(Pos(i, j));
            }
            table.push_back(row);
        }
    }

    // steps needed to transform 1 to 2
    int steps(vector<Pos>&);

    void printer() {
        cout << "\n--> Printing..." << endl;
        for (auto &r : table) {
            for (auto &c : r)
                cout << c << ' ';
            cout << endl;
        }
    }
};

int Mat::steps(vector<Pos>& vec) {
    while (true) {
        for (auto iter = ones.begin(); iter != ones.end(); ++iter) {
             
        }
    }
}

int main() {
    Mat m;
    m.read_input();
    m.printer();
    size_t sum = 0;
    for (auto &r : m.table) {
        for (auto &c : r)
            sum += c;
    }
    cout << "sum is: " << sum;
    return 0;
}
