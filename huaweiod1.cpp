#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;


double get_hulv_to_fen(const string& s)
{
    if (s == "CNY") return 100;
    if (s == "fen") return 1;
    if (s == "JPY")
    {
        return static_cast<double>(10000) / 1825;
    }
    if (s == "sen")
    {
        return static_cast<double>(100) / 1825;
    }
    if (s == "HKD")
    {
        return static_cast<double>(10000) / 123;
    }
    if (s == "cents")
    {
        return static_cast<double>(100) / 123;
    }
    if (s == "EUR")
    {
        return static_cast<double>(10000) / 14;
    }
    if (s == "eurocents")
    {
        return static_cast<double>(100) / 14;
    }
    if (s == "GBP")
    {
        return static_cast<double>(10000) / 12;
    }
    if (s == "pence")
    {
        return static_cast<double>(100) / 12;
    }
    return 1;
}


double convert2fen(const string& s)
{
    string a1, b1, a2, b2;
    bool is_combind = false;
    for (int i=0; i < s.size(); ++i)
    {
        if (i > 0 && isdigit(s[i]) && !isdigit(s[i-1]))
        {
            is_combind = true;
        }
        if (isdigit(s[i]) && !is_combind)
        {
            a1 += s[i];
        }
        if (isdigit(s[i]) && is_combind)
        {
            a2 += s[i];
        }
        if (!isdigit(s[i]) && !is_combind)
        {
            b1 += s[i];
        }
        if (!isdigit(s[i]) && is_combind)
        {
            b2 += s[i];
        }
    }
    
    if (!is_combind)
    {
        return get_hulv_to_fen(b1) * stoi(a1);
    }
    else
    {
        return get_hulv_to_fen(b2) * (stoi(a1) * 100 + stoi(a2));
    }
}


int main()
{
    int N;
    cin >> N;
    vector<string> records;
    records.reserve(N);
    string s;
    while (N--)
    {
        cin >> s;
        records.emplace_back(s);
    }
    // io done

    double sum = 0;
    for (auto& r : records)
    {
        sum += convert2fen(r);
    }
    cout << static_cast<int>(sum) << endl;
    return 0;

}
