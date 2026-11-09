#include <bits/stdc++.h>
using namespace std;
void solve() {
    int r, c, q;
    cin >> r >> c >> q;
    vector<string> g(r);
    for (int i = 0; i < r; i++) {
        cin >> g[i];
    }
    vector<vector<vector<int>>> comp(r, vector<vector<int>>(c, vector<int>(2, -1)));
    int current_comp_id = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int mode = 0; mode < 2; mode++) {
                if (comp[i][j][mode] != -1) continue;
                char ch = g[i][j];
                if (ch != '.' && !(ch == 'B' && mode == 0) && !(ch == 'R' && mode == 1)) {
                    continue;
                }
                queue<vector<int>> bfs;
                bfs.push({i, j, mode});
                comp[i][j][mode] = current_comp_id;
                while (!bfs.empty()) {
                    auto curr = bfs.front();
                    bfs.pop();
                    int x = curr[0], y = curr[1], m = curr[2];
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                            char nch = g[nx][ny];
                            if (nch == '.' || (nch == 'B' && m == 0) || (nch == 'R' && m == 1)) {
                                if (comp[nx][ny][m] == -1) {
                                    comp[nx][ny][m] = current_comp_id;
                                    bfs.push({nx, ny, m});
                                }
                            }
                        }
                    }
                    if (g[x][y] == '.') {
                        int nm = 1 - m;
                        if (comp[x][y][nm] == -1) {
                            comp[x][y][nm] = current_comp_id;
                            bfs.push({x, y, nm});
                        }
                    }
                }
                current_comp_id++;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        if (sx < 0 || sx >= r || sy < 0 || sy >= c || ex < 0 || ex >= r || ey < 0 || ey >= c) {
            cout << "NO\n";
            continue;
        }
        int start_comp = comp[sx][sy][0];
        int end_comp_blue = comp[ex][ey][0];
        int end_comp_red = comp[ex][ey][1];
        if (start_comp != -1 && (start_comp == end_comp_blue || start_comp == end_comp_red)) {
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
    return 0;
}
