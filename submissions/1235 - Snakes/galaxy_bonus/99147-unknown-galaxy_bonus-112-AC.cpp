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
    auto ok = [&](int r, int c, int m) {
        return r >= 0 && r < N && c >= 0 && c < M && (G[r][c] == '.' || G[r][c] == (m ? 'R' : 'B'));
    };
    vector<vector<int>> comp(2, vector<int>(N * M, -1));
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1}, k = 0;
    auto bfs = [&](int sr, int sc, int sm) {
        queue<array<int, 3>> q;
        comp[sm][sr * M + sc] = k, q.push({sr, sc, sm});
        while (!q.empty()) {
            auto [r, c, m] = q.front(); q.pop();
            if (G[r][c] == '.' && comp[!m][r * M + c] == -1) comp[!m][r * M + c] = k, q.push({r, c, !m});
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (ok(nr, nc, m) && comp[m][nr * M + nc] == -1) comp[m][nr * M + nc] = k, q.push({nr, nc, m});
            }
        }
        k++;
    };
    for (int r = 0; r < N; r++) for (int c = 0; c < M; c++) for (int m = 0; m < 2; m++)
        if (comp[m][r * M + c] == -1 && ok(r, c, m)) bfs(r, c, m);
    vector<string> ans;
    for (int i = 0; i < Q; i++) {
        int s = start[i].first * M + start[i].second, e = end[i].first * M + end[i].second;
        ans.push_back(comp[0][s] == comp[0][e] || comp[0][s] == comp[1][e] ? "YES" : "NO");
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
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
