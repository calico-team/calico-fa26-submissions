#include <bits/stdc++.h>
#define int long long

using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    char v[k];
    for (int i = 0; i < k; i++)
    {
        cin >> v[i];
    }
    char ans[n];
    for (char c : v)
    {
        for (int i = 0; i < n; i++)
        {
            cout << c;
        }
        cout << endl;
        string s;
        cin >> s;
        if (s == "CORRECT")
            return;
        for (int i = 0; i < n; i++)
        {
            if (s[i] != '_')
                ans[i] = c;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i];
    }
    cout << endl;
    string s;
    cin >> s;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
