#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    if (!(cin >> phase)) return 0;

    int n;
    cin >> n;

    if (phase == "FIRST") {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> p(n + 1, 0);
        auto dfs = [&](auto& self, int u, int f) -> void {
            p[u] = f;
            for (int v : adj[u]) {
                if (v != f) self(self, v, u);
            }
        };
        dfs(dfs, 1, 0);

        int x = 0;
        vector<int> a(n + 1);
        for (int i = 2; i <= n; ++i) {
            a[i] = p[i];
            x ^= a[i];
        }
        a[1] = x;

        for (int i = 1; i <= n; ++i) {
            cout << a[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    } else {
        vector<int> a(n + 1);
        int k = -1, x = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] == -1) k = i;
            else x ^= a[i];
        }
        a[k] = x;

        for (int i = 2; i <= n; ++i) {
            cout << i << " " << a[i] << "\n";
        }
    }

    return 0;
}