#include <bits/stdc++.h>

using namespace std;

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
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // States are (cell, mode); mode 0 = blue, 1 = red. Every move is reversible
    // (walking between two tiles active in the same mode, or spinning on a normal
    // tile), so reachability is just connected components: union-find.
    auto active = [&](int r, int c, int mode) {
        char ch = G[r][c];
        return ch == '.' || (ch == 'B' && mode == 0) || (ch == 'R' && mode == 1);
    };
    int total = N * M * 2;
    vector<int> par(total);
    iota(par.begin(), par.end(), 0);
    auto find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    };
    auto unite = [&](int a, int b) { par[find(a)] = find(b); };
    auto id = [&](int r, int c, int mode) { return (r * M + c) * 2 + mode; };
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++) {
            if (G[r][c] == '.') unite(id(r, c, 0), id(r, c, 1)); // spin
            for (int mode = 0; mode < 2; mode++) {
                if (!active(r, c, mode)) continue;
                if (r + 1 < N && active(r + 1, c, mode)) unite(id(r, c, mode), id(r + 1, c, mode));
                if (c + 1 < M && active(r, c + 1, mode)) unite(id(r, c, mode), id(r, c + 1, mode));
            }
        }
    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        int s = find(id(start[i].first, start[i].second, 0)); // start in blue mode
        bool ok = false;
        for (int mode = 0; mode < 2 && !ok; mode++) {
            int er = end[i].first, ec = end[i].second;
            if (active(er, ec, mode) && find(id(er, ec, mode)) == s) ok = true;
        }
        ans[i] = ok ? "YES" : "NO";
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
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
}
