#include <bits/stdc++.h>
using namespace std;

struct Query {
    int sr, sc, tr, tc;
    long long k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<string> g(n);
        for (auto &row : g) cin >> row;

        const int cells = n * m;
        const int total = 2 * cells;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        auto id = [m](int r, int c, int mode) {
            return mode * (m * 1000000) + r * m + c;
        };

        // State encoding: mode * cells + row * m + col.
        auto encode = [cells, m](int r, int c, int mode) {
            return mode * cells + r * m + c;
        };

        while (q--) {
            Query qu;
            cin >> qu.sr >> qu.sc >> qu.tr >> qu.tc >> qu.k;

            vector<int> dist(total, -1);
            queue<int> bfs;
            int start = encode(qu.sr, qu.sc, 0); // blue mode
            dist[start] = 0;
            bfs.push(start);

            int answer = -1;
            while (!bfs.empty()) {
                int v = bfs.front();
                bfs.pop();

                int mode = v / cells;
                int pos = v % cells;
                int r = pos / m;
                int c = pos % m;
                int d = dist[v];

                if (d > qu.k) continue;

                if (r == qu.tr && c == qu.tc) {
                    answer = d;
                    break;
                }

                auto push_state = [&](int nr, int nc, int nm) {
                    char ch = g[nr][nc];
                    bool active = (ch == '.') ||
                                  (ch == 'B' && nm == 0) ||
                                  (ch == 'R' && nm == 1);
                    if (!active) return;

                    int u = encode(nr, nc, nm);
                    if (dist[u] == -1) {
                        dist[u] = d + 1;
                        bfs.push(u);
                    }
                };

                if (g[r][c] == '.') {
                    int u = encode(r, c, mode ^ 1);
                    if (dist[u] == -1) {
                        dist[u] = d + 1;
                        bfs.push(u);
                    }
                }

                for (int z = 0; z < 4; ++z) {
                    int nr = r + dr[z], nc = c + dc[z];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                    push_state(nr, nc, mode);
                }
            }

            cout << ((answer != -1 && answer <= qu.k) ? "YES\n" : "NO\n");
        }
    }
    return 0;
}
