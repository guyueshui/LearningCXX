// see: https://blog.csdn.net/weixin_41937380/article/details/129139816
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int CalcMinIndent(vector<int>& nums)
{
    int ret = 0;
    while (true)
    {
        bool cont = false;
        int min = INT_MAX;
        int prev = 0, cur = 0;
        for (; cur < nums.size(); ++cur)
        {
            if (nums[cur] > 0)
            {
                // record sth
                if (!cont)
                {
                    cont = true;
                    prev = cur;
                }

                if (nums[cur] < min)
                {
                    min = nums[cur];
                }
            }
            else if (cont)
            {
                break;
            }
        }
        if (cont)
        {
            for (int i = prev; i < cur; ++i)
            {
                nums[i] -= min;
            }
            ret += min;
        }
        else break;
    }
    return ret;
}


int main()
{
    int n, h;
    cin >> n;
    vector<int> nums;
    nums.reserve(n);
    while (n--)
    {
        cin >> h;
        nums.push_back(h);
    }
    for (auto e : nums) cout << e << endl;

    int ret = CalcMinIndent(nums);
    cout << "ret=" << ret << endl;
    return 0;
}
