#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using op_t = pair<char, string>;


class WhitelistMgr
{
private:
    unordered_set<string> nml_lst_;
    unordered_set<string> reg_lst_;

    bool match_prefix_(const string& prefix, const string& target)
    {
        for (size_t i = 0; i < prefix.size(); ++i)
        {
            if (prefix[i] != target[i]) return false;
        }
        return true;
    }

public:
    bool is_in_white_list(const string& number)
    {
        if (nml_lst_.find(number) != nml_lst_.end()) return true;
        for (const string& e : reg_lst_)
        {
            if (match_prefix_(e, number)) return true;
        }
        return false;
    }

    void add_white_list(const string& number)
    {
        if (number.back() == '*')
        {
            string x = number;
            x.pop_back();
            reg_lst_.emplace(x);
        }
        else
        {
            nml_lst_.emplace(number);
        }
    }
};


int main()
{
    int n;
    char c;
    string s;

    cin >> n;
    vector<op_t> ops;
    ops.reserve(n);

    while (n--)
    {
        cin >> c >> s;
        ops.emplace_back(c, s);
    }
    // io done

    WhitelistMgr wm;
    vector<string> call_order;
    unordered_map<string, pair<int, int>> records;
    for (auto &op : ops)
    {
        if (op.first == 'W')
        {
            wm.add_white_list(op.second);
        }
        else if (op.first == 'C')
        {
            if (records.find(op.second) == records.end())
            {
                records[op.second] = {0, 0};
                call_order.emplace_back(op.second);
            }
            if (wm.is_in_white_list(op.second))
            {
                ++records[op.second].first;
            }
            else
            {
                ++records[op.second].second;
            }
        }
    }

    // output
    for (auto &e : call_order)
    {
        cout << e << " " << records[e].first << " " << records[e].second << endl;
    }
    return 0;
}
