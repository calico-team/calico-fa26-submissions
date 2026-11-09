#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t; cin >> t;
    while (t--) {
        int n, m, q; cin >> n >> m >> q;
        vector<vector<char>>grid(n, vector<char>(m));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m; j++) 
                cin >> grid[i][j];
        while (q--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            set<pair<int, int>>seen;
            vector<pair<int, int>>directions = {{1, 0}, {0,1}, {-1, 0}, {0, -1}};
            queue<pair<int, int>>q;
            seen.insert(make_pair(x1, y1));
            q.push(make_pair(x1, y1));
            while (!q.empty()) {
                int cx = q.front().first;
                int cy = q.front().second;
                q.pop();
                for (auto [x, y]: directions) {
                    int nx = cx+x, ny = cy+y;
                    if (seen.count({nx, ny})) continue;
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if ((grid[cx][cy] == 'R' && grid[nx][ny] == 'B') || (grid[cx][cy] == 'B' && grid[nx][ny] == 'R')) continue;
                    //cout << 'a' << nx << ' ' << ny << "\n";
                    seen.insert(make_pair(nx, ny));
                    q.push(make_pair(nx, ny));
                }
            }
            if (seen.count({x2, y2})) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        }
    }   
}
