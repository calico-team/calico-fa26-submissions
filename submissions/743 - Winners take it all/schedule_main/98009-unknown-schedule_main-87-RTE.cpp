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
        vector<int> p(n + 1), cnt(n + 1), cnt1(m + 1);
        vector<vector<int>> g(n + 1, vector<int> ());
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i] != 0)
                cnt[p[i]]++;
            g[p[i]].push_back(i);
        }

        vector<int> vis(n + 1, INF), fv(n + 1, INF);
        set<int> s;
        priority_queue<pair<int, int>> q;
        for (int i = 1; i <= n; i++) {
            if (p[i] == 0) {
                q.push({cnt[i], i});
                vis[i] = 0;
            }
        }
        for (int i = 1; i <= m; i++)
            s.insert(i);

        int c = 0;
        while (!q.empty()) {
            auto u = (q.top()).second;
            q.pop();
            if (c == (m * k) || c == n) {
                break;
            }
            if (vis[u] == 0) {
                vis[u] = 1 + (c / k);
                cnt1[vis[u]]++;
                if (cnt1[vis[u]] >= k)
                    s.erase(s.find(vis[u]));
            } else {
                if (!s.empty()) {
                    auto l = s.upper_bound(vis[u]);
                    if (l == s.end()) {
                        continue;
                    }
                    cnt1[*l]++;
                    if (cnt1[*l] >= k)
                        s.erase(l);
                    vis[u] = *l;
                } else break;
            }
            // if (u == 2) break;
            for (auto v : g[u]) {
                q.push({cnt[v], v});
                vis[v] = vis[u];
            }
            fv[u] = vis[u];
            c++;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (fv[i] <= m)
                ans++;

        cout << ans << '\n';
    }

    return 0;
}