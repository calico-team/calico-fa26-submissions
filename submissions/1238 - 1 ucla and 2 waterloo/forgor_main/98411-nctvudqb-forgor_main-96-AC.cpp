#include <bits/stdc++.h>
using namespace std;

string t;
int n;
vector<int> adj[200005];
int par[200005];

void dfs(int u, int p = -1) {
    par[u] = p;
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t >> n;
    if (t == "FIRST") {
        for (int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // arbitrarily root the tree at nod 1
        dfs(1);
        int cur = 0;
        for (int i = 2; i <= n; i++) {
            cur ^= par[i];
        }
        cout << cur << ' ';
        for (int i = 2; i <= n; i++) {
            cout << par[i] << ' ';
        }
        cout << '\n';
    } else {
        // reconstruct tree
        vector<int> info(n);
        for (auto &x : info) cin >> x;
        bool root_missing = (info[0] == -1);
        if (root_missing) {
            // all parents are given
            for (int i = 0; i < n; i++) {
                par[i+1] = info[i];
            }
        } else {
            // root given so we can recover the missing parent
            par[1] = -1;
            int root = info[0], missing_idx = -1;
            for (int i = 1; i < n; i++) {
                if (info[i] != -1) {
                    par[i+1] = info[i];
                    root ^= info[i];
                } else missing_idx = i;
            }
            // root is the missing parent
            par[missing_idx+1] = root;
        }

        for (int i = 1; i <= n; i++) {
            if (par[i] != -1) {
                cout << i << ' ' << par[i] << '\n';
            }
        }
    }
}