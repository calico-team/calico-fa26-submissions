#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int visited[205][205][2];
int cnt;

char graph[205][205];

void bfs(int sx, int sy, int n, int m) {
    queue<pair<pair<int, int>, int>> q;

    int first_state;
    if (graph[sx][sy] == 'R') first_state=0;
    else first_state=1;

    visited[sx][sy][first_state] = cnt;
    q.push({{sx, sy}, first_state});

    while (!q.empty()) {
        auto [coord, state] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = coord.first + dx[i];
            int ny = coord.second + dy[i];

            if (nx >= n || nx < 0) continue;
            if (ny >= m || ny < 0) continue;

            if (graph[nx][ny] == 'R' && state == 1) {
                if (graph[coord.first][coord.second] == '.') {
                    if (visited[nx][ny][1 - state] > 0) continue;
                    visited[nx][ny][1 - state] = cnt;
                    q.push({{nx, ny}, 1 - state});
                } 
                
                continue;
            }
            if (graph[nx][ny] == 'B' && state == 0) {
                if (graph[coord.first][coord.second] == '.') {
                    if (visited[nx][ny][1 - state] > 0) continue;
                    visited[nx][ny][1 - state] = cnt;
                    q.push({{nx, ny}, 1 - state});
                }

                continue;
            }

            if (visited[nx][ny][state] > 0) continue;
            visited[nx][ny][state] = cnt;
            q.push({{nx, ny}, state});
        }
    }
}

void solve() {
    int n, m, qu;
    cin >> n >> m >> qu;
    cnt = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j][0] = 0;
            visited[i][j][1] = 0;
        }
    }

    // blue = 1, red = 0
    for (int sx = 0; sx < n; sx++) {
        for (int sy = 0; sy < m; sy++) {
            if (graph[sx][sy] == 'R') {
                if (visited[sx][sy][0] > 0) continue;
            } else {
                // cout << visited[0][0][1] << "\n";
                if (visited[sx][sy][1] > 0) continue;
            }
            // cout << sx << " " << sy << "\n";
            // cout << sx << " " << sy << " " << n << " " << m << " " << cnt << "\n";
            bfs(sx, sy, n, m);
            cnt++;

            // cout << visited[0][0][1] << "\n";
        }
    }

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < n; j++) {
    //         for (int k = 0; k < m; k++) {
    //             // cout << j << " " << k << " " << i << " ";
    //             cout << visited[j][k][i] << " ";
    //         }
    //         cout << "\n";
    //     }
    //     cout << "\n";
    // }

    while (qu--) {
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;

        if (visited[startx][starty][1] == visited[endx][endy][1] || visited[startx][starty][1] == visited[endx][endy][0]) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}
