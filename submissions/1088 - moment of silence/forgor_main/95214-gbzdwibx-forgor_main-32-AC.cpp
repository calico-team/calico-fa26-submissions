#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair <int, int>;
vector <int> adj[200005];
int p[200005];
void dfs (int x, int par) {
    p[x] = par;
    for (auto i : adj[x]) if (i != par) dfs(i, x);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tc = 1;// cin >> tc;
    while (tc--) {
        string s; cin >> s;
        if (s == "FIRST") {
            int n; cin >> n;
            for (int i = 1; i <= n; i++) adj[i].clear();
            for (int i = 1; i < n; i++) {
                int u, v; cin >> u >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            dfs(1, -1);
            int g = 0;
            for (int i = 2; i <= n; i++) g ^= p[i];
            p[1] = g;
            for (int i = 1; i <= n; i++) cout << p[i] << ' ';
        }
        else {
            int n;cin >> n;
            int pp[n + 1];
            for (int i = 1; i <= n; i++) cin >> pp[i];
            int g = 0;
            for (int i = 1; i <= n; i++) if (pp[i] != -1) g ^= pp[i];
            for (int i = 1; i <= n; i++) if (pp[i] == -1) pp[i] = g;
            for (int i = 2; i <= n; i++) cout << pp[i] << ' ' << i << '\n';
        }
    }
}
