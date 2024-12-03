#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int cmp(const void* a, const void* b)
{
    int aa = *reinterpret_cast<const int*>(a);
    int bb = *reinterpret_cast<const int*>(b);
    if (aa < bb) return 1;
    if (aa ==  bb) return 0;
    else return -1;
}


int verify_mvp(const vector<int>& scores, int nmvp)
{
    vector<int> ret(nmvp);
    for (int i = 0; i < nmvp; ++i)
    {
        ret[i] = scores[i];
    }
    for (size_t i = nmvp; i < scores.size(); ++i)
    {
        auto m_it = std::min_element(ret.begin(), ret.end());
        *m_it += scores[i];
    }

    for (auto e : ret)
    {
        if (e != ret.back())
        {
            return -1;
        }
    }
    return ret.back();
}


int min_score_enlarge_nmvp(vector<int>& scores)
{
    if (scores.empty()) return 0;

    int min_score = INT_MAX;
    qsort(scores.data(), scores.size(), sizeof(int), cmp);

    for (size_t i = 1; i <= scores.size(); ++i)
    {
        int s = verify_mvp(scores, i);
        if (s > 0 && s < min_score)
        {
            min_score = s;
        }

    }
    return min_score;
}


int main()
{
    int score_minutes, temp;
    cin >> score_minutes;
    vector<int> scores;
    scores.reserve(score_minutes);
    while (score_minutes--)
    {
        cin >> temp;
        scores.push_back(temp);
    }
    // io done
    int ret = min_score_enlarge_nmvp(scores);
    cout << ret << endl;
    return 0;

}

int _main()
{
    vector<int> v {123,4,12,3,532,52,34,1,2,543,6,62};
    qsort(v.data(), v.size(), sizeof(int), cmp);
    for (auto e : v) cout << e << ' ';
    return 0;
}
