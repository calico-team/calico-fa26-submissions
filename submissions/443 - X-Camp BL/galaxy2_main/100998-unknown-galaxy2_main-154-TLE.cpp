#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
struct qqq {
    int r2, c2, k, id;
};
void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    vector<vector<qqq>> fro(n * m);
    for (int i = 0; i < q; ++i) {
        int r1, c1, r2, c2, k;
        cin >> r1 >> c1 >> r2 >> c2 >> k;
        fro[r1 * m + c1].push_back({r2, c2, k, i});
    }

    vector<string> ans(q);
    vector<vector<vector<int>>> dist(2, vector<vector<int>>(n, vector<int>(m, INF)));
    
    queue<tuple<int, int, int>> q_bfs;

    for (int src = 0; src < n * m; ++src) {
        if (fro[src].empty()) continue;

        int sr = src / m;
        int sc = src % m;

        for (int l = 0; l < 2; ++l) {
            for (int i = 0; i < n; ++i) {
                fill(dist[l][i].begin(), dist[l][i].end(), INF);
            }
        }

        dist[0][sr][sc] = 0;
        q_bfs.push({0, sr, sc});

        while (!q_bfs.empty()) {
            auto [lyr, r, c] = q_bfs.front();
            q_bfs.pop();
            int d = dist[lyr][r][c];

            if (grid[r][c] == '.') {
                int nxl = 1 - lyr;
                if (dist[nxl][r][c] > d + 1) {
                    dist[nxl][r][c] = d + 1;
                    q_bfs.push({nxl, r, c});
                }
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    char tile = grid[nr][nc];
                    bool can_walk = (tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R');
                    if (can_walk && dist[lyr][nr][nc] > d + 1) {
                        dist[lyr][nr][nc] = d + 1;
                        q_bfs.push({lyr, nr, nc});
                    }
                }
            }
        }
        for (const auto& qry : fro[src]) {
            int min_d = min(dist[0][qry.r2][qry.c2], dist[1][qry.r2][qry.c2]);
            if (min_d <= qry.k) {
                ans[qry.id] = "YES";
            } else {
                ans[qry.id] = "NO";
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
}