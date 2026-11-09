#include <bits/stdc++.h>
using namespace std;

bool bfs(int rs, int cs, int re, int ce, vector<vector<char>> grid, int n, int m) {
    queue<tuple<int, int, int>> q;
    q.push({rs, cs, 0});
    vector<vector<vector<bool>>> visited(2, vector<vector<bool>>(n, vector<bool>(m, false)));
    // cout << "hi\n";
    while(!q.empty()) {
        auto [r, c, type] = q.front();
        q.pop();
        vector<pair<int, int>> neighbours = {{r+1, c}, {r-1, c}, {r, c+1}, {r, c-1}};
        for (auto [nr, nc] : neighbours) {
            // cout << nr << " " << nc << "\n";
            if (nr >= n || nr < 0 || nc >= m || nc < 0) continue;
            if (visited[type][nr][nc]) continue;
            if ((type == 0 && grid[nr][nc] != 'R') || (type == 1 && grid[nr][nc] != 'B')) {
                visited[type][nr][nc] = true;
                q.push({nr, nc, type});
                if (grid[nr][nc] == '.') {
                    if (visited[!type][nr][nc]) continue;
                    visited[!type][nr][nc] = true;
                    q.push({nr, nc, !type});
                }
            }
        }
        if (visited[0][re][ce] || visited[1][re][ce]) return true;
    }
    return false;
}


int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<char>> grid(n, vector<char>(m));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> grid[i][j];
        for (int i = 0; i < q; i++) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            cout << (bfs(rs, cs, re, ce, grid, n, m) ? "YES\n" : "NO\n");
        }
    }
    return 0;
}