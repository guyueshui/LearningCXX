#include<iostream>
#include<vector>

using namespace std;

class Cash {
public:
    int m;
    int n;
    vector<int> koc;

    Cash(int _m, int _n) : m(_m), n(_n) { }

    int func(int m, int n) {
        if (m == 0) return 1;
        else if (m < 0 || n == -1) return 0;
        else
            return func(m, n-1)
                + func(m - koc[n-1], n);
    }
};


int main(){
    int m, n;
    cin >> m >> n;
    
    Cash cc(m, n);

    for (int i=0; i!=n; ++i) {
        int tmp;
        cin >> tmp;
        cc.koc.push_back(tmp);
    }
    
    cout << cc.func(m, n);
    
}
