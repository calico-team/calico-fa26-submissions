#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9 + 7;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
struct qq {
    int r1, c1, r2, c2, k, id;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m, q; cin >> n >> m >> q;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        vector<qq> qq(q);
        vector<vector<int>> qsc(n * m);
        for (int i = 0; i < q; ++i) {
            cin >> qq[i].r1 >> qq[i].c1 >> qq[i].r2 >> qq[i].c2 >> qq[i].k;
            qq[i].id = i;
            qsc[qq[i].r1 * m + qq[i].c1].push_back(i);
        }
        vector<string> ans(q);
        vector<vector<vector<int>>> dist(2, vector<vector<int>>(n, vector<int>(m, INF)));
        for (int src = 0; src < n * m; ++src) {
            if (qsc[src].empty()) continue;
            int sr = src / m; int sc = src % m;
            for (int lyr = 0; lyr < 2; ++lyr) {
                for (int i = 0; i < n; ++i) {
                    fill(dist[lyr][i].begin(), dist[lyr][i].end(), INF);
                }
            }
            queue<pair<int, pair<int, int>>> q_bfs;
            dist[0][sr][sc] = 0;
            q_bfs.push({0, {sr, sc}});
            while (!q_bfs.empty()) {
                auto curr = q_bfs.front();
                q_bfs.pop();
                int lyr = curr.first;
                int r = curr.second.first;
                int c = curr.second.second;
                if (grid[r][c] == '.') {
                    int nxl = 1 - lyr;
                    if (dist[nxl][r][c] == INF) {
                        dist[nxl][r][c] = dist[lyr][r][c] + 1;
                        q_bfs.push({nxl, {r, c}});
                    }
                }
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        char tile = grid[nr][nc];
                        bool can_walk = (tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R');
                        if (can_walk && dist[lyr][nr][nc] == INF) {
                            dist[lyr][nr][nc] = dist[lyr][r][c] + 1;
                            q_bfs.push({lyr, {nr, nc}});
                        }
                    }
                }
            }
            for (int dx : qsc[src]) {
                int tr = qq[dx].r2;
                int tc = qq[dx].c2;
                int tk = qq[dx].k;
                int min_d = min(dist[0][tr][tc], dist[1][tr][tc]);
                if (min_d <= tk) {
                    ans[dx] = "YES";
                } else {
                    ans[dx] = "NO";
                }
            }
        }
        for (int i = 0; i < q; ++i) {
            cout << ans[i] << "\n";
        }
    }
}