
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
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
        for (int i = 0; i < N; i++)
            cin >> grid[i];

        DSU dsu(N * M);

        auto canConnect = [](char a, char b) {
            return a == b || a == '.' || b == '.';
        };

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                int id = r * M + c;

                if (r > 0 &&
                    canConnect(grid[r][c], grid[r - 1][c])) {
                    dsu.unite(id, id - M);
                }

                if (c > 0 &&
                    canConnect(grid[r][c], grid[r][c - 1])) {
                    dsu.unite(id, id - 1);
                }
            }
        }

        while (Q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;

            int start = rs * M + cs;
            int end = re * M + ce;

            if (dsu.find(start) == dsu.find(end))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}
