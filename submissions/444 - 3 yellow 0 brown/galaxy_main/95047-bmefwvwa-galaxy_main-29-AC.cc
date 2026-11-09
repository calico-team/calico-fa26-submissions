#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return 1;
    }
};

void ac() {
    int n, m, q; cin >> n >> m >> q;    
    string grid;
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        grid += row;
    }
    auto id = [&](int r, int c) { return r * m + c; };
    dsu uf(n * m);
    auto conn = [&](int u, int v) {
        if (min(u, v) < 0 || max(u, v) >= n * m) return;
        if (grid[u] != '.' && grid[v] != '.' && grid[u] != grid[v]) return;
        uf.join(u, v);
    };
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (r + 1 < n) conn(id(r, c), id(r + 1, c));
            if (c + 1 < m) conn(id(r, c), id(r, c + 1));
        }
    }
    while (q--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << array{"NO", "YES"}[uf.same(id(a, b), id(c, d))] << "\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}