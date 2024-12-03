#include <iostream>
#include <vector>

using namespace std;


int count(int n_goat, int n_wolf, int n_load)
{
    int goat_l = n_goat, goat_r = 0,
        wolf_l = n_wolf, wolf_r = 0;

    int ret = 0;
    int pw = n_load / 2;
    int pg = n_load - pw;

    while (goat_l > 0 || wolf_l > 0)
    {
        int _pw = pw, _pg = pg;

        wolf_r = min(_pw, wolf_l);
        goat_r = min(goat_l, _pg);
        
        if (goat_r <= wolf_r)
        {
            _pw -= 1;
            wolf_r = max(0, wolf_r - 1);
        }


        wolf_l = max(wolf_l - _pw, 0);
        goat_l = max(goat_l - _pg, 0);

        ret += 1;
    }
    return ret;
}


int main()
{
    int n_goat, n_wolf, n_load;
    cin >> n_goat >> n_wolf >> n_load;
    // io done
    cout << count(n_goat, n_wolf, n_load) << endl;
    return 0;
}
