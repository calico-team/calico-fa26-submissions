#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int n, m, q, r1, c1, r2, c2;
vector<vector<char>> g;
vector<vector<int>> vis;

void bfs(int x, int y, int mark) {
    queue<pair<int, int>> q;
    q.push({x, y});
    vis[x][y] = mark;
    while(!q.empty()) {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        for(int k = 0; k < 4; k++) {
            int nx = curx + dx[k];
            int ny = cury + dy[k];
            if(1 <= nx && nx <= n && 1 <= ny && ny <= m && vis[nx][ny] == 0) {
                bool bad = (g[curx][cury] == 'R' && g[nx][ny] == 'B') || (g[curx][cury] == 'B' && g[nx][ny] == 'R');
                if(!bad) {
                    q.push({nx, ny});
                    vis[nx][ny] = mark;
                }
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> m >> q;
        g.clear();
        vis.clear();
        g.resize(n+1, vector<char>(m+1));
        vis.resize(n+1, vector<int>(m+1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cin >> g[i][j];
            }
        }
        int idx = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(!vis[i][j]) {
                    bfs(i, j, idx);
                    idx++;
                }
            }
        }

        for(int i = 0; i < q; i++) {
            cin >> r1 >> c1 >> r2 >> c2;
            if(vis[r1+1][c1+1] == vis[r2+1][c2+1]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}