#include <bits/stdc++.h>
using namespace std;
const int mxd = 1000005;
int dist[2][1005][1005];
int rip[2 * mxd];
struct qqq {
    int r2, c2, k, id;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m, q;
        if (!(cin >> n >> m >> q)) break;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        vector<vector<qqq>> qsc(n * m);
        for (int i = 0; i < q; ++i) {
            int r1, c1, r2, c2, k;
            cin >> r1 >> c1 >> r2 >> c2 >> k;
            qsc[r1 * m + c1].push_back({r2, c2, k, i});
        }
        vector<string> ans(q);
        for (int src = 0; src < n * m; ++src) {
            if (qsc[src].empty()) continue;
            int sr = src / m;
            int sc = src % m;
            for (int i = 0; i < n; ++i) {
                memset(dist[0][i], 0x3f, m * sizeof(int));
                memset(dist[1][i], 0x3f, m * sizeof(int));
            }
            int head = 0, tail = 0;
            dist[0][sr][sc] = 0;
            rip[tail++] = (0 << 20) | (sr << 10) | sc;
            while (head < tail) {
                int curr = rip[head++];
                int lyr = curr >> 20;
                int r = (curr >> 10) & 1023;
                int c = curr & 1023;
                
                int d_curr = dist[lyr][r][c];
                
                if (grid[r][c] == '.') {
                    int nxl = 1 - lyr;
                    if (dist[nxl][r][c] > d_curr + 1) {
                        dist[nxl][r][c] = d_curr + 1;
                        rip[tail++] = (nxl << 20) | (r << 10) | c;
                    }
                }
                
                if (r > 0) {
                    char tile = grid[r-1][c];
                    if ((tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R')) {
                        if (dist[lyr][r-1][c] > d_curr + 1) {
                            dist[lyr][r-1][c] = d_curr + 1;
                            rip[tail++] = (lyr << 20) | ((r-1) << 10) | c;
                        }
                    }
                }
                if (r < n - 1) {
                    char tile = grid[r+1][c];
                    if ((tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R')) {
                        if (dist[lyr][r+1][c] > d_curr + 1) {
                            dist[lyr][r+1][c] = d_curr + 1;
                            rip[tail++] = (lyr << 20) | ((r+1) << 10) | c;
                        }
                    }
                }
                if (c > 0) {
                    char tile = grid[r][c-1];
                    if ((tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R')) {
                        if (dist[lyr][r][c-1] > d_curr + 1) {
                            dist[lyr][r][c-1] = d_curr + 1;
                            rip[tail++] = (lyr << 20) | (r << 10) | (c-1);
                        }
                    }
                }
                if (c < m - 1) {
                    char tile = grid[r][c+1];
                    if ((tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R')) {
                        if (dist[lyr][r][c+1] > d_curr + 1) {
                            dist[lyr][r][c+1] = d_curr + 1;
                            rip[tail++] = (lyr << 20) | (r << 10) | (c+1);
                        }
                    }
                }
            }   
            for (const auto& qry : qsc[src]) {
                int min_d = min(dist[0][qry.r2][qry.c2], dist[1][qry.r2][qry.c2]);
                ans[qry.id] = (min_d <= qry.k) ? "YES" : "NO";
            }
        }       
        for (int i = 0; i < q; ++i) {
            cout << ans[i] << "\n";
        }
    }
}