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
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int V = N * M * 2;
    vector<int> pr(V);
    for (int i = 0; i < V; i++) pr[i] = i;

    auto get = [&](int x) {
        while (pr[x] != x) {
            pr[x] = pr[pr[x]];
            x = pr[x];
        }
        return x;
    };
    auto join = [&](int a, int b) {
        a = get(a);
        b = get(b);
        if (a != b) pr[b] = a;
    };
    auto good = [&](int r, int c, int m) {
        if (G[r][c] == '.') return true;
        if (G[r][c] == 'B') return m == 0;
        return m == 1;
    };

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            for (int m = 0; m < 2; m++) {
                if (!good(r, c, m)) continue;
                int u = ((r * M + c) << 1) | m;
                for (int k = 0; k < 4; k++) {
                    int nr = r + dx[k];
                    int nc = c + dy[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!good(nr, nc, m)) continue;
                    join(u, ((nr * M + nc) << 1) | m);
                }
                if (G[r][c] == '.') join(u, ((r * M + c) << 1) | (m ^ 1));
            }
        }
    }

    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        int s = get(((start[i].first * M + start[i].second) << 1));
        int er = end[i].first, ec = end[i].second;
        int okk = 0;
        for (int m = 0; m < 2; m++) {
            if (!good(er, ec, m)) continue;
            if (get(((er * M + ec) << 1) | m) == s) okk = 1;
        }
        ans[i] = okk ? "YES" : "NO";
    }
    return ans;
}

int main() {
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
