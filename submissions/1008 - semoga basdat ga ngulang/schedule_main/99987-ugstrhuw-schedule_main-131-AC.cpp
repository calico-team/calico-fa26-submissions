
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define abysr ios_base::sync_with_stdio(0); cin.tie(0);

vector<int> adj[10005];
ll sz[10005];

ll dfs(int u) {
    sz[u] = 1;

    for (auto v : adj[u]) {
        sz[u] += dfs(v);
    }

    return sz[u];
}

int main() {
    abysr

    ll t = 1;
    cin >> t;

    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;

        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            sz[i] = 0;
        }

        vector<int> root;

        for (int i = 1; i <= n; i++) {
            ll p;
            cin >> p;

            if (p == 0) {
                root.push_back(i);
            } else {
                adj[p].push_back(i);
            }
        }

        for (auto u : root) {
            dfs(u);
        }

        priority_queue<pair<ll, ll>> pq;

        for (auto u : root) {
            pq.push({sz[u], u});
        }

        ll ans = 0;

        while (m-- && !pq.empty()) {
            vector<int> temp;

            ll cnt = min(k, (ll)pq.size());

            while (cnt--) {
                ll u = pq.top().second;
                pq.pop();

                ans++;
                temp.push_back(u);
            }

            for (auto u : temp) {
                for (auto v : adj[u]) {
                    pq.push({sz[v], v});
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
