#include <cctype>
#include <cwctype>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

using namespace std;

void parse_log(string& logline, vector<pair<string, string>> out)
{
    istringstream is(logline);
    for (string s; getline(is, s, ',');)
    {
        size_t pos = s.find(':');
        string k, v;
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (i < pos)
            {
                k.push_back(s[i]);
            }
            else if (i > pos)
            {
                v.push_back(s[i]);
            }
        }
        out.emplace_back(k, v);
    }
}

string to_lower(string s)
{
    string ret(s);
    for (size_t i = 0; i < s.size(); ++i)
    {
        ret[i] = tolower(s[i]);
    }
    return ret;
}

bool is_keyword(string s, unordered_set<string> kw_lst)
{
    string ls = to_lower(s);
    return kw_lst.find(ls) != kw_lst.end();
}

string process_value(const string& key, string& value)
{
    // end with ip
    if (key.size() >= 2 && std::tolower(key.back()) == 'p' &&
            std::tolower(key[key.size() - 2]) == 'i')
    {
        size_t dot_pos1 = value.find('.');
        size_t dot_pos2 = value.find('.', dot_pos1 + 1);
        value.replace(dot_pos1 + 1, dot_pos2 - (dot_pos1 + 1), "***");
        dot_pos2 = dot_pos1 + 4;
        size_t dot_pos3 = value.find('.', dot_pos2 + 1);
        value.replace(dot_pos2 + 1, dot_pos3 - (dot_pos2 + 1), "***");
        return value;
    }
    // not quite understand the rule
    return value;
}


int main()
{
    int n;
    string kw;
    cin >> n;
    unordered_set<string> kw_lst;
    kw_lst.reserve(n);
    while (n--)
    {
        cin >> kw;
        kw_lst.emplace(to_lower(kw));
    }

    string logline;
    cin >> logline;
    // io done

    vector<pair<string, string>> log_lst;
    parse_log(logline, log_lst);

    for (auto &e : log_lst)
    {
        if (e.first == "password" || e.first == "pwd")
        {
            e.second = "******";
        }
        else if (is_keyword(e.first, kw_lst))
        {
            e.second = process_value(e.first, e.second);
        }
    }

    // output
    for (size_t i = 0; i < log_lst.size(); ++i)
    {
        cout << log_lst[i].first << ":" << log_lst[i].second;
        if (i != (log_lst.size() - 1)) cout << ",";
    }
    return 0;
}
