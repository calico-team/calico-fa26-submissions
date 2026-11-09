#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t; cin >> t;
    while (t--) {
        int n, m,tt; cin >> n >> m >> tt;
        vector<vector<char>>grid(n, vector<char>(m));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m; j++) 
                cin >> grid[i][j];
        vector<vector<bool>>seen(n+1,vector<bool>(m+1,0));
        vector<pair<int, int>>directions = {{1, 0}, {0,1}, {-1, 0}, {0, -1}};
        queue<pair<int, int>>q;
        seen[n-1][m-1]=1;
        q.push(make_pair(n-1,m-1));
        while (!q.empty()) {
            int cx = q.front().first;
            int cy = q.front().second;
            q.pop();
            for (auto [x, y]: directions) {
                int nx = cx+x, ny = cy+y;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (seen[nx][ny]) continue;
                if ((grid[cx][cy] == 'R' && grid[nx][ny] == 'B') || (grid[cx][cy] == 'B' && grid[nx][ny] == 'R')) continue;
                //cout << 'a' << nx << ' ' << ny << "\n";
                seen[nx][ny]=1;
                q.push(make_pair(nx, ny));
            }
        }
        // if (seen[x2][y2]) cout << "YES" << "\n";
        // else cout << "NO" << "\n";
        while (tt--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(seen[x1][y1])cout<<"YES"<<"\n";
            else cout<<"NO"<<"\n";
            // vector<vector<bool>>seen(n+1,vector<bool>(m+1,0));
            // vector<pair<int, int>>directions = {{1, 0}, {0,1}, {-1, 0}, {0, -1}};
            // queue<pair<int, int>>q;
            // seen[x1][y1]=1;
            // q.push(make_pair(x1, y1));
            // while (!q.empty()) {
            //     int cx = q.front().first;
            //     int cy = q.front().second;
            //     q.pop();
            //     for (auto [x, y]: directions) {
            //         int nx = cx+x, ny = cy+y;
            //         if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            //         if (seen[nx][ny]) continue;
            //         if ((grid[cx][cy] == 'R' && grid[nx][ny] == 'B') || (grid[cx][cy] == 'B' && grid[nx][ny] == 'R')) continue;
            //         //cout << 'a' << nx << ' ' << ny << "\n";
            //         seen[nx][ny]=1;
            //         q.push(make_pair(nx, ny));
            //     }
            // }
            // if (seen[x2][y2]) cout << "YES" << "\n";
            // else cout << "NO" << "\n";
        }
    }   
}
