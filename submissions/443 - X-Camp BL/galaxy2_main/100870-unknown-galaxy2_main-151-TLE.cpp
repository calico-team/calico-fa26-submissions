#include <bits/stdc++.h>
using namespace std;

const int MAXNM = 100005; 
const int INF = 1e9 + 7;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

struct qq {
    int r1, c1, r2, c2, k, id;
};

int dist[2 * MAXNM]; 

struct State {
    int lyr, r, c;
};
State q_bfs[2 * MAXNM];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        vector<qq> queries(q);
        vector<vector<int>> qsc(n * m);
        for (int i = 0; i < q; ++i) {
            cin >> queries[i].r1 >> queries[i].c1 >> queries[i].r2 >> queries[i].c2 >> queries[i].k;
            queries[i].id = i;
            qsc[queries[i].r1 * m + queries[i].c1].push_back(i);
        }

        vector<string> ans(q);
        int total_cells = n * m;

        for (int src = 0; src < total_cells; ++src) {
            if (qsc[src].empty()) continue;

            int sr = src / m;
            int sc = src % m;

            fill(dist, dist + 2 * total_cells, INF);

            int head = 0, tail = 0;
            dist[0 * total_cells + sr * m + sc] = 0;
            q_bfs[tail++] = {0, sr, sc};

            while (head < tail) {
                State curr = q_bfs[head++];
                int lyr = curr.lyr;
                int r = curr.r;
                int c = curr.c;
                int curr_idx = lyr * total_cells + r * m + c;

                if (grid[r][c] == '.') {
                    int nxl = 1 - lyr;
                    int nxl_idx = nxl * total_cells + r * m + c;
                    if (dist[nxl_idx] == INF) {
                        dist[nxl_idx] = dist[curr_idx] + 1;
                        q_bfs[tail++] = {nxl, r, c};
                    }
                }

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        char tile = grid[nr][nc];
                        bool can_walk = (tile == '.') || (lyr == 0 && tile == 'B') || (lyr == 1 && tile == 'R');
                        
                        if (can_walk) {
                            int nxt_idx = lyr * total_cells + nr * m + nc;
                            if (dist[nxt_idx] == INF) {
                                dist[nxt_idx] = dist[curr_idx] + 1;
                                q_bfs[tail++] = {lyr, nr, nc};
                            }
                        }
                    }
                }
            }

            for (int dx : qsc[src]) {
                int tr = queries[dx].r2;
                int tc = queries[dx].c2;
                int tk = queries[dx].k;

                int d0 = dist[0 * total_cells + tr * m + tc];
                int d1 = dist[1 * total_cells + tr * m + tc];
                int min_d = min(d0, d1);

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
