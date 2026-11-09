#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases = 0;
    cin >> cases;
    cin.ignore(1000, '\n');
    for (int _ = 0; _ < cases; ++_)
    {

        int n, r;
        cin >> n >> r;

        bool one = true;
        int prev_one = 0;

        bool two = true;
        int prev_two = 0;

        int curTime = 0;

        bool bad = false;

        for (int i = 0; i < n; ++i)
        {
            cin >> curTime;

            if (bad)
            {
                continue;
            }

            if (!one)
            {
                if ((curTime - prev_one) / r > 0)
                {
                    one = true;
                }
            }
            else if (one && !two)
            {
                if ((curTime - prev_two) / r > 0)
                {
                    two = true;
                }
            }

            if (!one && !two)
            {
                bad = true;
                continue;
            }

            if (two)
            {
                two = false;
                prev_two = curTime;
            }
            else
            {
                one = false;
                prev_one = curTime;
                prev_two = curTime;
            }
        }

        if (bad)
        {
            cout << "NO" << '\n';
        }
        else
        {
            cout << "YES" << '\n';
        }

        // REMEMBER TO CLEAN UP OUTPUT FOR SUBMISSION!!!
    }
    return 0;
}