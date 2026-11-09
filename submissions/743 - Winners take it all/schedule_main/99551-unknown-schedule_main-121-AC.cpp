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

        vector<pair<int, int>> v;
        for (int i = 1; i <= n; i++)
            v.push_back({lv[i], i});

        sort(v.rbegin(), v.rend());
        set<int> s;
        for (int i = 1; i <= m; i++)
            s.insert(i);

        int ans = 0;
        vector<int> vis(n + 1, INF), cnt(m + 1);
        vis[0] = 0;
        for (auto i : v) {
            int x = i.second;
            if (vis[x] != INF) continue;
            vector<int> vec;
            while (vis[x] == INF) {
                vec.push_back(x);
                x = p[x];
            }

            reverse(vec.begin(), vec.end());
            auto l = s.upper_bound(vis[x]);
            if (l != s.end()) {
                for (auto j : vec) {
                    vis[j] = *l;
                    cnt[*l]++;
                    ans++;
                    l++;
                    if (l == s.end()) break;
                }
                for (auto j : vec)
                    if (vis[j] != INF && cnt[vis[j]] == k) {
                        s.erase(vis[j]);
                    }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}