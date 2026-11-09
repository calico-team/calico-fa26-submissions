#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<int>> g(n + 1);
        for (int i = 1, p; i <= n; i++) {
            cin >> p;
            g[p].push_back(i);
        }

        vector<int> h(n + 1);
        auto dfs = [&](auto&& dfs, int v) -> void { for (int c : g[v]) dfs(dfs, c), h[v] = max(h[v], h[c] + 1);
        };
        dfs(dfs, 0);


        priority_queue<pair<int, int>> pq;
        pq.push({h[0], 0});
        int ans = -1;
        for (int s = 0; s <= m && !pq.empty(); s++) {
            vector<int> cur;
            while (!pq.empty() && (int)cur.size() < k) cur.push_back(pq.top().second), pq.pop();
            ans += cur.size();
            for (int v : cur) for (int c : g[v]) pq.push({h[c], c});
        }
        cout << ans << '\n';
    }
}
