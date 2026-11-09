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

        for (int i = 0; i < N; i++) {
            cin >> grid[i];
        }


        int total = N * M * 2;
        DSU dsu(total);

        auto getID = [&](int r, int c, int mode) {
            return (r * M + c) * 2 + mode;
        };

        auto active = [&](int r, int c, int mode) {
            char ch = grid[r][c];

            if (ch == '.') return true;
            if (ch == 'B') return mode == 0;
            if (ch == 'R') return mode == 1;

            return false;
        };

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {

                if (grid[r][c] == '.') {
                    dsu.unite(
                        getID(r, c, 0),
                        getID(r, c, 1)
                    );
                }

                int dr[] = {0, 1};
                int dc[] = {1, 0};

                for (int k = 0; k < 2; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= N || nc >= M)
                        continue;

                    for (int mode = 0; mode < 2; mode++) {
                        if (active(r, c, mode) &&
                            active(nr, nc, mode)) {

                            dsu.unite(
                                getID(r, c, mode),
                                getID(nr, nc, mode)
                            );
                        }
                    }
                }
            }
        }

        while (Q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;

            int start = getID(rs, cs, 0);

            int startRoot = dsu.find(start);

            bool possible = false;

            if (active(re, ce, 0)) {
                if (dsu.find(getID(re, ce, 0)) == startRoot) {
                    possible = true;
                }
            }

            if (active(re, ce, 1)) {
                if (dsu.find(getID(re, ce, 1)) == startRoot) {
                    possible = true;
                }
            }

            cout << (possible ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
