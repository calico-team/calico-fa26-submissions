#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<char> a(k);
    for(auto &e : a) cin >> e;

    string ans(n, '_');
    string input(n, '_');

    int idx = 0;
    while(input != "CORRECT")
    {
        ans = input;
        for(int i = 0; i < n; i++)
        {
            if(ans[i] == '_') ans[i] = a[idx];
        }

        idx++;
        cout << ans << "\n";
        cout.flush();
        cin >> input;
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}