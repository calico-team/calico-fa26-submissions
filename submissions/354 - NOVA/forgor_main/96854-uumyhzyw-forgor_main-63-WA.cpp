#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t;
    if (!(cin >> t)) return 0;

    long long P = 999983;

    if (t == "FIRST") {
        int n;
        if (!(cin >> n)) return 0;
        vector<vector<int>> adj(n + 1);
        rep(i, 0, n - 1) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> p(n + 1, 0);
        auto dfs = [&](auto& self, int u, int fa) -> void {
            p[u] = fa;
            trav(v, adj[u]) {
                if (v != fa) self(self, v, u);
            }
        };
        dfs(dfs, 1, 0);

        vector<long long> a(n + 1, 0);
        long long s = 0;
        rep(i, 1, n) {
            a[i] = p[i];
            s = (s + a[i]) % P;
        }
        a[n] = (P - s) % P;

        rep(i, 1, n + 1) {
            cout << a[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    } else {
        int n;
        if (!(cin >> n)) return 0;
        vector<long long> a(n + 1);
        int k = -1;
        long long s = 0;
        rep(i, 1, n + 1) {
            cin >> a[i];
            if (a[i] == -1) {
                k = i;
            } else {
                s = (s + a[i]) % P;
            }
        }
        long long missing = (P - s) % P;
        a[k] = missing;

        vector<int> p(n + 1);
        rep(i, 1, n + 1) p[i] = a[i];

        rep(i, 2, n + 1) {
            cout << i << " " << p[i] << "\n";
        }
    }

    return 0;
}