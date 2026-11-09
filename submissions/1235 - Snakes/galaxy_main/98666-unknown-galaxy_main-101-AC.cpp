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
    vector<vector<int>> vis(2, vector<int>(N * M));
    queue<array<int, 3>> q;
    for (int m = 0; m < 2; m++) if (ok(N - 1, M - 1, m)) vis[m][N * M - 1] = 1, q.push({N - 1, M - 1, m});
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [r, c, m] = q.front(); q.pop();
        if (G[r][c] == '.' && !vis[!m][r * M + c]) vis[!m][r * M + c] = 1, q.push({r, c, !m});
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (ok(nr, nc, m) && !vis[m][nr * M + nc]) vis[m][nr * M + nc] = 1, q.push({nr, nc, m});
        }
    }
    vector<string> ans;
    for (auto [r, c] : start) ans.push_back(vis[0][r * M + c] ? "YES" : "NO");
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
