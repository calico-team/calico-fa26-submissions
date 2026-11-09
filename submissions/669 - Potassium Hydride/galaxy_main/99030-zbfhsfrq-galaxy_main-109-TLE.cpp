#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

void solve() {
    int n, m, qu;
    cin >> n >> m >> qu;

    char graph[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph[i][j];
        }
    }

    while (qu--) {
        bool good = false;

        pair<int, int> start;
        pair<int, int> last;
        cin >> start.first >> start.second;
        cin >> last.first >> last.second;

        bool visited[n][m][2];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j][0] = false;
                visited[i][j][1] = false;
            }
        }

        // 1 - Blue , 0 - Red
        queue<pair<pair<int, int>, int>> q;

        visited[start.first][start.second][1] = true;
        q.push({{start.first, start.second}, 1});

        while (!q.empty()) {
            auto [coord, state] = q.front();
            q.pop();

            if (coord.first == last.first && coord.second == last.second) {
                cout << "YES\n";
                good = true;
                break;
            }

            // cout << "\n";
            // cout << coord.first << " " << coord.second << " " << state << "\n";

            for (int i = 0; i < 4; i++) {
                int nx = coord.first + dx[i];
                int ny = coord.second + dy[i];

                // cout << nx << " " << ny << "\n";

                if (nx >= n || nx < 0) continue;
                if (ny >= m || ny < 0) continue;

                if (graph[nx][ny] == 'R' && state == 1) {
                    if (graph[coord.first][coord.second] == '.') {
                        if (visited[nx][ny][1 - state]) continue;
                        visited[nx][ny][1 - state] = true;
                        q.push({{nx, ny}, 1 - state});
                    } 
                    
                    continue;
                }
                if (graph[nx][ny] == 'B' && state == 0) {
                    if (graph[coord.first][coord.second] == '.') {
                        if (visited[nx][ny][1 - state]) continue;
                        visited[nx][ny][1 - state] = true;
                        q.push({{nx, ny}, 1 - state});
                    }

                    continue;
                }

                if (visited[nx][ny][state]) continue;
                visited[nx][ny][state] = true;
                q.push({{nx, ny}, state});
            }
        }

        if (!good) cout << "NO\n";
    }
}

int main() {
    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}
