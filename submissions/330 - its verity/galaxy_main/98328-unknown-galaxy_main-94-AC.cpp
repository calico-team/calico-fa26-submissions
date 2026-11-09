#include <bits/stdc++.h>

using namespace std;
#define sz(x) ((int)x.size())
typedef long long ll;
int n, m, k, p, x, y, r, c, nx, ny;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n --) {
        cin >> m >> k >> p;
        char grid[m][k];
        int vis[m][k] = {0};
        deque<vector<int>> q;
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        string s;
        for (int i = 0; i < m; i ++) {
            cin >> s;
            for (int j = 0; j < k; j ++) {
                grid[i][j] = s[j];
                vis[i][j] = 0;
            }
        }
        int cur = 1;
        for (int i = 0; i < m; i ++) {
            for (int j = 0; j < k; j ++) {
                if (grid[i][j] == '.' && vis[i][j] == 0) {
                    q.push_back({i, j}); vis[i][j] = cur;
                    while (sz(q) > 0) {
                        y = q.front()[0]; x = q.front()[1]; q.pop_front();
                        for (vector<int> l : dir) {
                            ny = y + l[0]; nx = x + l[1];
                            if (ny >= 0 && ny < m && nx >= 0 && nx < k && (grid[y][x] == '.' || grid[y][x] == grid[ny][nx] || grid[ny][nx] == '.') && vis[ny][nx] == 0) {
                                vis[ny][nx] = cur;
                                q.push_back({ny, nx});
                            }
                        }
                    }
                    cur ++;
                }
            }

        }
        for (int i = 0; i < p; i ++) {
            cin >> x >> y >> r >> c;
            if (vis[x][y] == vis[r][c]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
