#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define all(v) begin(v), end(v)
using ll = long long;

//const ll MOD = 998244353;
const ll MOD = 1e9+7;

const ll INFL = 1e18;
const int INF = 1e9;


struct trie {
    struct node {
        int cnt=0;
        int c[2] = {};
    };
    vector<node> t={{}};
    void add(int x) {
        int v = 0;
        t[v].cnt++;
        for (int j=29; j>=0; j--) {
            int b= x>>j&1;
            if (!t[v].c[b]) {
                t[v].c[b] =t.size(); 
                t.push_back({});
            }
            v = t[v].c[b];
            t[v].cnt++;
        }
    }
    void del(int x)  {
        int v= 0 ;
        t[v].cnt--;
        for (int j=29; j>=0; j--) {
            int b=  x>>j&1;
            v = t[v].c[b];
            assert(v);
            t[v].cnt--;
        }
    }
    int mx(int y) {
        int x = 0;
        int v = 0;
        for (int j=29; j>=0; j--) {
            int b = y>>j&1;
            if (t[v].c[!b] && t[t[v].c[!b]].cnt) {
                x |= 1<<j;
                v = t[v].c[!b];
            } else {
                v = t[v].c[b];
            }
            assert(v);
        }
        return x;
    }
};

void $() {
    // cycle nodes
    // dfs from these and keep trie
    // queries for eeach cycle node
    // both directions
    int n;
    cin >> n;
    vector<int> par(n), val(n);
    for (auto &u: par) {
        cin >> u;
        u--;
    }
    for (auto &u: val) cin >> u;
    trie t_dfs;
    vector<int> ans(n);
    vector<char> cc(n), vis(n);
    vector<vector<array<int, 2>>> query(n);
    vector<vector<int>> cycles;
    for (int i=0; i<n; i++) if (!vis[i]) {
        int u = i;
        vector<int> cyc;
        while (true) {
            vis[u] = true;
            cyc.push_back(u);
            if (vis[par[u]]) break;
            u = par[u];
        }
        cyc.erase(cyc.begin(), find(all(cyc), par[u]));
        if (cyc.empty()) continue;
        for (int v: cyc) cc[v] = true;
        reverse(all(cyc));
        cycles.push_back(cyc);
    }
    vector<vector<int>> adj(n);
    for (int i=0; i<n; i++) if (!cc[i]) adj[par[i]].push_back(i);
    t_dfs.add(0);
    auto dfs = [&](int v, int rt, int xr, auto &&self) -> void {
        xr ^= val[v];
        t_dfs.add(xr);
        ans[v] = t_dfs.mx(xr);
        query[rt].push_back({v, xr});
        for (int u: adj[v]) {
            self(u, rt, xr, self);
        }
        t_dfs.del(xr);
    };
    for (int i=0; i<n; i++) if (cc[i]) dfs(i, i, 0, dfs);
    for (auto &c: cycles) {
        trie tt;
        int xr = 0;
        for (int i=0; i<2*c.size(); i++) {
            tt.add(xr);
            for (auto [v, xp]: query[c[i%c.size()]]) {
                ans[v] = max(ans[v], tt.mx(xp^xr));
            }
            xr ^= val[c[i%c.size()]];
        }
    }
    for (int x: ans) cout << x << ' ';
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc=1;
    cin >> tc;
    while (tc--) $();
}
