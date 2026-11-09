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
    vector<vector<int>> board(N, vector<int>(M, -1));
    int curr = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // floodfill
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (board[r][c] != -1) continue;
            
            queue<pair<int, int>> q;
            q.push({r, c});
            board[r][c] = curr;

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                char curr_color = G[cr][cc];

                for (int i = 0; i < 4; ++i) {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];

                    if (nr >= 0 && nr < N && nc >= 0 && nc < M && board[nr][nc] == -1) {
                        char neighbor_color = G[nr][nc];

                        if (curr_color == '.' || neighbor_color == '.' || (curr_color == neighbor_color)) {
                            board[nr][nc] = curr;
                            q.push({nr, nc});
                        }
                    }
                }
            }
            
            curr++;
        }
    }
   
    
    // queries
    vector<string> results;
    for (int i = 0; i < Q; ++i) {
        int sr = start[i].first;
        int sc = start[i].second;
        int er = end[i].first;
        int ec = end[i].second;

        if (board[sr][sc] != -1 && (board[sr][sc] == board[er][ec])) {
            results.push_back("YES");
        } else {
            results.push_back("NO");
        }
    }

    return results;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("01_bonus.in", "r", stdin);

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
