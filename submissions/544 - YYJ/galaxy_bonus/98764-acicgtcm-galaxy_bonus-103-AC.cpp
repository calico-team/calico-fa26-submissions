#include <iostream>
#include <vector>
using namespace std;

int n, m, q, cnt;
vector<string> g;
vector<vector<vector<int>>> vis;
int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void floodfill(int x, int y, int mode) {
    // if (vis[x][y][mode]) return;
    // vis[x][y][mode] = true;
    if (vis[x][y][mode] > -1) return;
    vis[x][y][mode] = cnt;
    
    // if (g[x][y] == '.' && !vis[x][y][1 - mode]) floodfill(x, y, 1 - mode);
    if (g[x][y] == '.' && vis[x][y][1 - mode] == -1) floodfill(x, y, 1 - mode); 
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i][0], ny = y + dirs[i][1];
        // if (nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny][mode]) continue;
        if (nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny][mode] > -1) continue;
        if ((mode == 0 && g[nx][ny] == 'R') || (mode == 1 && g[nx][ny] == 'B')) continue;
        floodfill(nx, ny, mode);
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> q; g.clear(); g.resize(n);
        for (int i = 0; i < n; i++) cin >> g[i];
        
        // vis.clear(); vis.resize(n, vector<vector<bool>> (m, vector<bool> (2, false)));
        vis.clear(); vis.resize(n, vector<vector<int>> (m, vector<int> (2, -1))); cnt = 0;
        // if (g[n - 1][m - 1] == '.' || g[n - 1][m - 1] == 'B') floodfill(n - 1, m - 1, 0);
        // else floodfill(n - 1, m - 1, 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if ((g[i][j] == '.' || g[i][j] == 'B') && vis[i][j][0] == -1) { floodfill(i, j, 0); cnt++; }
                else if (g[i][j] == 'R' && vis[i][j][1] == -1) { floodfill(i, j, 0); cnt++; }
            }
        
        while (q--) {
            int sx, sy, dx, dy; cin >> sx >> sy >> dx >> dy;
            // cout << (vis[sx][sy][0] ? "YES\n" : "NO\n");
            if (g[dx][dy] == '.' || g[dx][dy] == 'B') cout << (vis[sx][sy][0] == vis[dx][dy][0] ? "YES\n" : "NO\n");
            else if (g[dx][dy] == 'R') cout << (vis[sx][sy][0] == vis[dx][dy][1] ? "YES\n" : "NO\n");
        }
    }
}
