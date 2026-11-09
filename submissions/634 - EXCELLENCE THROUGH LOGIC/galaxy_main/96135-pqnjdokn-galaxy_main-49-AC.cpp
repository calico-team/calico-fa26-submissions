
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
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);

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

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int total = n * m;
    DSU dsu(2 * total);

    auto id = [&](int r, int c, int mode) {
        return mode * total + r * m + c;
    };

    auto active = [&](int r, int c, int mode) {
        char ch = grid[r][c];

        if (ch == '.') return true;
        if (ch == 'R') return mode == 1;
        return mode == 0;
    };

    int dr[] = {0, 1};
    int dc[] = {1, 0};

    for (int mode = 0; mode < 2; mode++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {

                if (!active(r, c, mode)) continue;

                for (int d = 0; d < 2; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr >= n || nc >= m) continue;

                    if (active(nr, nc, mode)) {
                        dsu.unite(
                            id(r, c, mode),
                            id(nr, nc, mode)
                        );
                    }
                }
            }
        }
    }

    // Spin action on normal tiles
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '.') {
                dsu.unite(
                    id(r, c, 0),
                    id(r, c, 1)
                );
            }
        }
    }

    while (q--) {
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;

        int start = id(rs, cs, 0);

        bool possible = false;

        if (grid[re][ce] == '.') {
            possible = dsu.same(start, id(re, ce, 0)) ||
                        dsu.same(start, id(re, ce, 1));
        }
        else if (grid[re][ce] == 'B') {
            possible = dsu.same(start, id(re, ce, 0));
        }
        else {
            possible = dsu.same(start, id(re, ce, 1));
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
}

void read_your_input() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_your_input();

    return 0;
}
