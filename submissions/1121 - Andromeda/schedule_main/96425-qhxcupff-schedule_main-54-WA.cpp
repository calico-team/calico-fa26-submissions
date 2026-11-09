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

    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        auto [node, cur] = q.front();
        q.pop();
        for (int child : children[node])
        {
            while (num[cur] == k && cur < m)
                cur++;
            if (cur >= m)
                break;
            num[cur]++;
            q.push({child, cur + 1});
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
