// Source: https://usaco.guide/general/io
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

 constexpr static int dx[4] = {-1, 0, 0, 1};
 constexpr static int dy[4] = {0, -1, 1, 0};






vector<string> solve(int N, int M, int Q, vector<string>& g, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    vector<string> ans;

    for (int qr = 0; qr < Q; qr++) {
        vector<vector<vector<bool>>> vis(N, vector<vector<bool>>(M, vector<bool>(2, false)));
        queue<tuple<int, int, bool>> q;
        int sx = start[qr].first;
        int sy = start[qr].second;
        q.push({sx, sy, false});
        q.push({sx, sy, true});
        vis[sx][sy][0] = true;
        vis[sx][sy][1] = true;

        bool hasmade = false;
        while (!q.empty()) {
            auto [x, y, m] = q.front();

            q.pop();
            if (x == end[qr].first && y == end[qr].second) {
                hasmade = true;
                break;
            }
            for (int mode = 0; mode < 2; mode++) {
                if (g[x][y] != '.' && mode != m) {
                    continue;
                }
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx < 0 || nx >= N || ny < 0 || ny >= M ||
                    (g[nx][ny] == 'R' && mode != 0) || 
                    (g[nx][ny] == 'B' && mode != 1) || vis[nx][ny][mode]) continue;

                    vis[nx][ny][mode] = true;
                    q.push({nx, ny, mode});
                }
            }
        }

        if (hasmade) ans.push_back("YES");
        else {ans.push_back("NO");}


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
