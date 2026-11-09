#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<string> g;
vector<vector<vector<bool>>> vis;
int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void floodfill(int x, int y, int mode) {
    if (vis[x][y][mode]) return;
    vis[x][y][mode] = true;
    
    if (g[x][y] == '.' && !vis[x][y][1 - mode]) floodfill(x, y, 1 - mode);
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i][0], ny = y + dirs[i][1];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny][mode]) continue;
        if ((mode == 0 && g[nx][ny] == 'R') || (mode == 1 && g[nx][ny] == 'B')) continue;
        floodfill(nx, ny, mode);
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> q; g.clear(); g.resize(n);
        for (int i = 0; i < n; i++) cin >> g[i];
        
        vis.clear(); vis.resize(n, vector<vector<bool>> (m, vector<bool> (2, false)));
        if (g[n - 1][m - 1] == '.' || g[n - 1][m - 1] == 'B') floodfill(n - 1, m - 1, 0);
        else floodfill(n - 1, m - 1, 1);
        
        while (q--) {
            int sx, sy, dx, dy; cin >> sx >> sy >> dx >> dy;
            cout << (vis[sx][sy][0] ? "YES\n" : "NO\n");
        }
    }
}
