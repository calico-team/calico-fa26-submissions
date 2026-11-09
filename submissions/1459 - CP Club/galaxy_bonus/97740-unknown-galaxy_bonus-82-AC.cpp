#include <iostream>
#include <queue>
using namespace std;

int n, m, q;
char grid[210][210] = {};
int group[210][210] = {};
int gidx = 0;

void clear() {
    for (int i = 0; i < 210; i++) for (int j = 0; j < 210; j++) group[i][j] = -1;
    gidx = 0;
}

typedef pair<int, int> pii; // {x, y};
pii offsets[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void propagate(int sx, int sy) {
    queue<pii> q;
    q.push({sx, sy});
    while (!q.empty()) {
        pii cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        if (group[x][y] != -1) continue;
        group[x][y] = gidx;
        if (grid[x][y] == '.') {
            for (pii off : offsets) {
                int nx = x + off.first;
                int ny = y + off.second;
                if (nx < 0 || nx >= m) continue;
                if (ny < 0 || ny >= n) continue;
                if (group[nx][ny] != -1) continue;
                q.push({nx, ny});
            }
        } else if (grid[x][y] == 'R') {
            for (pii off : offsets) {
                int nx = x + off.first;
                int ny = y + off.second;
                if (nx < 0 || nx >= m) continue;
                if (ny < 0 || ny >= n) continue;
                if (group[nx][ny] != -1) continue;
                if (grid[nx][ny] == 'B') continue;
                q.push({nx, ny});
            }
        } else if (grid[x][y] == 'B') {
            for (pii off : offsets) {
                int nx = x + off.first;
                int ny = y + off.second;
                if (nx < 0 || nx >= m) continue;
                if (ny < 0 || ny >= n) continue;
                if (group[nx][ny] != -1) continue;
                if (grid[nx][ny] == 'R') continue;
                q.push({nx, ny});
            }
        }
    }
    gidx++;
}

void print() {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) cout << group[x][y] << " ";
        cout << endl;
    }
}

void solve() {
    cin >> n >> m >> q;
    for (int y = 0; y < n; y++) for (int x = 0; x < m; x++) cin >> grid[x][y]; 
    clear();
    for (int rep = 0; rep < q; rep++) {
        int sy, sx, ey, ex;
        cin >> sy >> sx >> ey >> ex;
        if (group[sx][sy] == -1) propagate(sx, sy);
        
        if (group[sx][sy] == group[ex][ey]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}