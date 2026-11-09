#include <bits/stdc++.h>
using namespace std;
void solve() {
    int r, c, q;
    cin >> r >> c >> q;
    vector<string> g(r);
    for (int i = 0; i < r; i++) {
        cin >> g[i];
    }
    vector<array<int, 4>> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2] >> qs[i][3];
    }
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (auto [sx, sy, ex, ey] : qs) {
        if (sx < 0 || sx >= r || sy < 0 || sy >= c || ex < 0 || ex >= r || ey < 0 || ey >= c) {
            cout << "NO\n";
            continue;
        }
        queue<array<int, 3>> bfs;
        vector<vector<array<bool, 2>>> vis(r, vector<array<bool, 2>>(c, {false, false}));
        bfs.push({sx, sy, 0});
        vis[sx][sy][0] = true;
        bool ok = false;
        while (!bfs.empty()) {
            auto [x, y, mode] = bfs.front();
            bfs.pop();
            if (x == ex && y == ey) {
                ok = true;
                break;
            }
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                    char ch = g[nx][ny];
                    if (ch == '.' || (ch == 'B' && mode == 0) || (ch == 'R' && mode == 1)) {
                        if (!vis[nx][ny][mode]) {
                            vis[nx][ny][mode] = true;
                            bfs.push({nx, ny, mode});
                        }
                    }
                }
            }
            if (g[x][y] == '.') {
                int nmode = 1 - mode;
                if (!vis[x][y][nmode]) {
                    vis[x][y][nmode] = true;
                    bfs.push({x, y, nmode});
                }
            }
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}