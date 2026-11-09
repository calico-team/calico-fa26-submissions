#include <iostream>
#include <vector>
#include <queue>

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





    // YOUR CODE HERE
    vector<string> ans(Q, "NO");

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < Q; i++) {
        vector<vector<vector<bool>>> visited(
            N, vector<vector<bool>>(M, vector<bool>(2, false))
        );

        queue<pair<pair<int, int>, int>> q;

        int sr = start[i].first;
        int sc = start[i].second;
        int er = end[i].first;
        int ec = end[i].second;

        q.push({{sr, sc}, 0});
        visited[sr][sc][0] = true;

        
        bool f = false;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            int r = current.first.first;
            int c = current.first.second;
            int mode = current.second;

            if (r == er && c == ec) {
                f = true;
                break;
            }
            if (G[r][c] == '.') {
                int nm = 1 - mode;

                if (!visited[r][c][nm]) {
                    visited[r][c][nm] = true;
                    q.push({{r, c}, nm});
                }
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
                    continue;
                }

                char tile = G[nr][nc];

                bool valid = (tile == '.') ||
                             (mode == 0 && tile == 'B') ||
                             (mode == 1 && tile == 'R');

                if (valid && !visited[nr][nc][mode]) {
                    visited[nr][nc][mode] = true;
                    q.push({{nr, nc}, mode});
                }
            }







            
        }

        if (f) {
            ans[i] = "YES";
        }
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

    return 0;
}
