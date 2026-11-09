#include "bits/stdc++.h"

using namespace std;

#define int long long

const int N = 2e5 + 10;
const int md = 1e9 + 7;
const int INF = 1e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> p(n + 1), lv(n + 1);
        vector<vector<int>> g(n + 1, vector<int> ());
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            g[p[i]].push_back(i);
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (p[i] == 0) {
                lv[i] = 1;
                q.push(i);
            }
        }

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : g[u]) {
                lv[v] = lv[u] + 1;
                q.push(v);
            }
        }

        vector<int> cnt(m + 1);
        for (int i = 1; i <= n; i++)
            cnt[lv[i]]++;

        int ans = 0;
        for (int i = 1; i <= m; i++)
            ans += min(cnt[i], k);

        cout << ans << '\n';
    }

    return 0;
}