/*
 * Build a Spiral matrix in clockwise order
 * Microsoft 2019 interview
 */

#include <vector>
#include <iostream>
#include <iomanip> // for using setw()

using namespace std;

class Mat {
private:
    int n; // nxn matrix
    vector<vector<int> > mat;
    // is current coordinate a border?
    bool isBorder(const int, const int);

public:
    // constructor
    Mat(int _n) {
        n = _n;
        while (_n--) {
            // for a temp object, use `vector<int>()`
            mat.push_back(vector<int>(n, 0));
        }
    }
    ~Mat(void) = default;
    void buildMat(void);
    void printer(void);
};

/*
 * Basic idea:
 *     1. populate the matrix until a border is reached
 *     2. once reach a border, change directions,
 *        the directions is given by [0,1,2,3] which
 *        represent [right, down, left, up]
 *     3. until n^2 elements are all populated
 * 
 * Note: populate from large to small
 */

void Mat::buildMat() {
    int n2 = n*n;
    int i = 0, 
        j = 0,
        direction = 0;
    
    while (n2) {
        direction %= 4; // --> [0,1,2,3]
        while (!isBorder(i,j)) {
            if (direction == 0) {
                mat[i][j++] = n2--;
                if (isBorder(i,j)) {
                    j--;
                    i++;
                    break;
                }
            }
            if (direction == 1) {
                mat[i++][j] = n2--;
                if (isBorder(i,j)) {
                    i--;
                    j--;
                    break;
                }
            }
            if (direction == 2) {
                mat[i][j--] = n2--;
                if (isBorder(i,j)) {
                    j++;
                    i--;
                    break;
                }
            }
            if (direction == 3) {
                mat[i--][j] = n2--;
                if (isBorder(i,j)) {
                    i++;
                    j++;
                    break;
                }
            }
        }
        ++direction; // change the direction
    }
}

bool Mat::isBorder(const int _i, const int _j) 
{
    if (_i == n 
        || _i == -1 
        || _j == n 
        || _j == -1
        || mat[_i][_j] != 0) return true;
    return false;
}

void Mat::printer() {
    for (auto &row : mat) {
        for (auto &col : row) {
            cout << setw(3) << col << ' ';
        }
        cout << endl;
    }
}

// entrance
int main() {
    Mat m(4);
    m.buildMat();
    m.printer();
    return 0;
}
