#include <bits/stdc++.h>
using namespace std;
struct State {
    int r, c, m;
};
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;    
        vector<vector<vector<bool>> > vis(n, vector<vector<bool>>(m, vector<bool>(2, false)));
        queue<State> qu;
        qu.push({r1, c1, 0});
        vis[r1][c1][0] = true;
        bool found = false;
        while (!qu.empty()) {
            auto [cr, cc, cm] = qu.front();
            qu.pop();
            if (cr == r2 && cc == c2) {
                found = true;
                break;
            }
            for (int d = 0; d < 4; ++d) {
                int nr = cr + dr[d];
                int nc = cc + dc[d];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    char tile = grid[nr][nc];
                    if (tile == '.' || (tile == 'B' && cm == 0) || (tile == 'R' && cm == 1)) {
                        if (!vis[nr][nc][cm]) {
                            vis[nr][nc][cm] = true;
                            qu.push({nr, nc, cm});
                        }
                    }
                }
            }
            if (grid[cr][cc] == '.') {
                int nm = 1 - cm;
                if (!vis[cr][cc][nm]) {
                    vis[cr][cc][nm] = true;
                    qu.push({cr, cc, nm});
                }
            }
        }
        if (found) {
            cout << "YES\n";
        }
        else {
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
}