
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<string> g(n);
    for (int i = 0; i < n; i++)
        cin >> g[i];

    int total = n * m;
    DSU dsu(2 * total);

    auto id = [&](int r, int c, int mode) {
        return mode * total + r * m + c;
    };

    auto active = [&](int r, int c, int mode) {
        if (g[r][c] == '.') return true;
        if (g[r][c] == 'B') return mode == 0;
        return mode == 1;
    };

    for (int mode = 0; mode < 2; mode++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (!active(r, c, mode)) continue;

                if (r + 1 < n && active(r + 1, c, mode))
                    dsu.unite(id(r, c, mode), id(r + 1, c, mode));

                if (c + 1 < m && active(r, c + 1, mode))
                    dsu.unite(id(r, c, mode), id(r, c + 1, mode));
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] == '.') {
                dsu.unite(id(r, c, 0), id(r, c, 1));
            }
        }
    }

    while (q--) {
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;

        int start = id(rs, cs, 0);

        bool possible = false;

        if (g[re][ce] == '.') {
            possible = dsu.same(start, id(re, ce, 0));
        }
        else if (g[re][ce] == 'B') {
            possible = dsu.same(start, id(re, ce, 0));
        }
        else {
            possible = dsu.same(start, id(re, ce, 1));
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
