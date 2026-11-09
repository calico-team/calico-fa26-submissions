#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p;
        children[p].push_back(i);
    }
    int num[m];
    memset(num, 0, sizeof(num));

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 0});
    int slot = 0;

    while (!q.empty())
    {
        auto [cur, node] = q.top();
        q.pop();
        slot = max(slot, cur);

        for (int child : children[node])
        {
            while (slot < m && num[slot] == k)
                slot++;
            if (slot >= m)
                break;
            num[slot]++;
            q.push({cur + 1, child});
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        ans += num[i];
    }
    cout << ans << endl;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
