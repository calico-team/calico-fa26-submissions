
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n), sz(n, 1) {
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

        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);

        for (auto &row : grid)
            cin >> row;

        DSU dsu(N * M);

        auto id = [&](int r, int c) {
            return r * M + c;
        };

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {

                if (r + 1 < N &&
                    (grid[r][c] == '.' ||
                     grid[r + 1][c] == '.' ||
                     grid[r][c] == grid[r + 1][c])) {

                    dsu.unite(id(r, c), id(r + 1, c));
                }

                if (c + 1 < M &&
                    (grid[r][c] == '.' ||
                     grid[r][c + 1] == '.' ||
                     grid[r][c] == grid[r][c + 1])) {

                    dsu.unite(id(r, c), id(r, c + 1));
                }
            }
        }

        while (Q--) {
            int sr, sc, er, ec;
            cin >> sr >> sc >> er >> ec;

            if (dsu.find(id(sr, sc)) ==
                dsu.find(id(er, ec))) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
