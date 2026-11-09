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

 constexpr int dx[4] = {-1, 0, 0, 1};
 constexpr int dy[4] = {0, -1, 1, 0};
vector<string> solve(int N, int M, int Q, vector<string>& g, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    vector<string> ans;

    vector<vector<vector<bool>>> vis(N, vector<vector<bool>>(M, vector<bool>(2, false)));
    queue<tuple<int, int, bool>> q;
    int sx = N-1;
    int sy = M-1;

    if (g[sx][sy] == '.') {
        q.push({sx, sy, 0});
        q.push({sx, sy, 1});

        vis[sx][sy][0] = true;
        vis[sx][sy][1] = true;
    }
    else if (g[sx][sy] == 'B') {
        q.push({sx, sy, 0});
        vis[sx][sy][0] = true;
    }
    else {
        q.push({sx, sy, 1});
        vis[sx][sy][1] = true;
    }




    while (!q.empty()) {
        auto [x, y, m] = q.front();

        q.pop();
        if (g[x][y] == '.') {
            int nm = 1 - m;
        
            if (!vis[x][y][nm]) {
                vis[x][y][nm] = true;
                q.push({x, y, nm});
            }
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

            if (g[nx][ny] == 'B' && m != 0) continue;
            if (g[nx][ny] == 'R' && m != 1) continue;
            if (vis[nx][ny][m]) continue;

            vis[nx][ny][m] = true;
            q.push({nx, ny, m});
        }
    }

    for (int i = 0; i < Q; i++) {
        int stx = start[i].first;
        int sty = start[i].second;
        if (vis[stx][sty][0] || vis[stx][sty][1]) {
            ans.push_back("YES");
        }
        else {
            ans.push_back("NO");
        }
    }
    return ans;
}



int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
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
