#include <bits/stdc++.h>
using namespace std;

struct Components {
    vector<int> parent, size;
    explicit Components(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    void join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> grid(n);
        for (auto &row : grid) cin >> row;
        Components components(2 * n * m);
        auto id = [m](int row, int col, int mode) { return 2 * (row * m + col) + mode; };
        auto active = [&](int row, int col, int mode) {
            return grid[row][col] == '.' || grid[row][col] == "BR"[mode];
        };
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (grid[r][c] == '.') components.join(id(r, c, 0), id(r, c, 1));
                for (int mode = 0; mode < 2; ++mode) {
                    if (!active(r, c, mode)) continue;
                    if (r && active(r - 1, c, mode))
                        components.join(id(r, c, mode), id(r - 1, c, mode));
                    if (c && active(r, c - 1, mode))
                        components.join(id(r, c, mode), id(r, c - 1, mode));
                }
            }
        }
        while (q--) {
            int sr, sc, er, ec;
            cin >> sr >> sc >> er >> ec;
            int mode = grid[er][ec] == 'R';
            cout << (components.find(id(sr, sc, 0)) == components.find(id(er, ec, mode))
                         ? "YES\n" : "NO\n");
        }
    }
}
