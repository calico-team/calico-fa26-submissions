#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    int tc;
    cin >> tc;

    while (tc--)
    {
        int n, r;
        vector<int> a;
        cin >> n >> r;

        for (int i = 0; i < n; i++)
        {
            int a_i;
            cin >> a_i;
            a.push_back(a_i);
        }

        int max = 2;
        int next_reload = r;
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (max > 0)
            {
                max--;
            }
            else
            {
                if (a[i] < a[i - 1] + r)
                {
                    cout << "NO";
                    flag = false;
                    break;
                }
            }
        }

        if (flag)
            cout << "YES";
        cout << "\n";
    }
    return 0;
}
