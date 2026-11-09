#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define tii tuple<int, int, char>

int t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        int n, m, qu;
        cin >> n >> m >> qu;
        vector<string> a(n);
        for (auto &x : a) cin >> x;
        // allowed[i][j][0] = can reach (i, j) with red
        // allowed[i][j][1] = can reach (i, j) with blue
        int allowed[205][205][2] = {};
        int vis[205][205][2] = {};

        queue<tii> q;
        q.push({n-1, m-1, 'R'});
        q.push({n-1, m-1, 'B'});
        while (!q.empty()) {
            auto [x, y, color] = q.front();
            q.pop();
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (vis[x][y][!!(color == 'R')]) continue;
            vis[x][y][!!(color == 'R')] = 1;
            if (a[x][y] != '.' && color != a[x][y]) continue;
            allowed[x][y][!!(color == 'R')] = 1;
            q.push({x-1, y, color});
            q.push({x+1, y, color});
            q.push({x, y-1, color});
            q.push({x, y+1, color});
            if (a[x][y] == '.') {
                char other = (color == 'R' ? 'B' : 'R');
                q.push({x, y, other}); // can change color at the same cell
            }
        }

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         if (allowed[i][j][0] && allowed[i][j][1]) cout << 'X';
        //         else if (allowed[i][j][0]) cout << 'B';
        //         else if (allowed[i][j][1]) cout << 'R';
        //         else cout << '.';
        //     }
        //     cout << '\n';
        // }

        while (qu--) {
            int x, y, a, b;
            cin >> x >> y >> a >> b;
            if (allowed[x][y][0]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}