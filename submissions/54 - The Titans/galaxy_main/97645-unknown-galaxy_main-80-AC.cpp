#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void solve() {
    int n, m, q; if (!(cin >> n >> m >> q)) return;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(2, false)));
    
    queue<pair<pair<int, int>, int>> qu;
    
    int dest_r = n - 1; int dest_c = m - 1; char dest_char = grid[dest_r][dest_c];
    
    if (dest_char == 'B') {
        vis[dest_r][dest_c][0] = true;
        qu.push({{dest_r, dest_c}, 0});
    } else if (dest_char == 'R') {
        vis[dest_r][dest_c][1] = true; qu.push({{dest_r, dest_c}, 1});
    } else {
        vis[dest_r][dest_c][0] = true; vis[dest_r][dest_c][1] = true;
        qu.push({{dest_r, dest_c}, 0}); qu.push({{dest_r, dest_c}, 1});
    }
    
    int dr[] = {-1, 1, 0, 0}; int dc[] = {0, 0, -1, 1};
    
    while (!qu.empty()) {
        auto curr = qu.front(); qu.pop();
        
        int r = curr.first.first; int c = curr.first.second; int mode = curr.second;

        if (grid[r][c] == '.') {
            int next_mode = 1 - mode;
            if (!vis[r][c][next_mode]) {
                vis[r][c][next_mode] = true;
                qu.push({{r, c}, next_mode});
            }
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                char target_char = grid[nr][nc];
                bool active = false;
                if (target_char == '.') {
                    active = true;
                } else if (mode == 0 && target_char == 'B') {
                    active = true;
                } else if (mode == 1 && target_char == 'R') {
                    active = true;
                }
                
                if (active && !vis[nr][nc][mode]) {
                    vis[nr][nc][mode] = true;
                    qu.push({{nr, nc}, mode});
                }
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        
        if (vis[r1][c1][0]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}