
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
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
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

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */
vector<string> solve(
    int N,
    int M,
    int Q,
    vector<string>& G,
    vector<pair<int, int>>& start,
    vector<pair<int, int>>& end
) {
    int total = 2 * N * M;

    DSU dsu(total);

    auto active = [&](int r, int c, int mode) -> bool {
        if (G[r][c] == '.') return true;

        if (G[r][c] == 'B') return mode == 0;

        return mode == 1;
    };

    auto id = [&](int r, int c, int mode) -> int {
        return 2 * (r * M + c) + mode;
    };

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {

            if (G[r][c] == '.') {
                dsu.unite(
                    id(r, c, 0),
                    id(r, c, 1)
                );
            }

            // Check right and down neighbors.
            int dr[2] = {0, 1};
            int dc[2] = {1, 0};

            for (int k = 0; k < 2; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= N || nc >= M) continue;

                for (int mode = 0; mode < 2; mode++) {

                    if (active(r, c, mode) &&
                        active(nr, nc, mode)) {

                        dsu.unite(
                            id(r, c, mode),
                            id(nr, nc, mode)
                        );
                    }
                }
            }
        }
    }

    vector<string> ans;
    ans.reserve(Q);

    for (int i = 0; i < Q; i++) {

        int sr = start[i].first;
        int sc = start[i].second;

        int er = end[i].first;
        int ec = end[i].second;

        int source = dsu.find(id(sr, sc, 0));

        bool possible = false;

        for (int mode = 0; mode < 2; mode++) {

            if (!active(er, ec, mode))
                continue;

            int destination = dsu.find(id(er, ec, mode));

            if (source == destination) {
                possible = true;
                break;
            }
        }

        ans.push_back(possible ? "YES" : "NO");
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {

        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);

        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }

        vector<pair<int, int>> start, end;

        for (int j = 0; j < Q; j++) {

            int start_row, start_col;
            int end_row, end_col;

            cin >> start_row >> start_col
                >> end_row >> end_col;

            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }

    return 0;
}
