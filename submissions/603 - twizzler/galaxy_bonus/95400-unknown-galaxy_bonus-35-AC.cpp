#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> g(n);
        for (auto &row : g) {
            cin >> row;
        }

        auto active = [&](int r, int c, int mode) {
            if (g[r][c] == '.') {
                return true;
            }
            if (g[r][c] == 'B') {
                return mode == 0;
            }
            return mode == 1;
        };

        vector<int> comp(n * m * 2, -1);
        int cnt = 0;
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                for (int mode = 0; mode < 2; mode++) {
                    int id = (r * m + c) * 2 + mode;
                    if (comp[id] != -1 || !active(r, c, mode)) {
                        continue;
                    }
                    comp[id] = cnt;
                    queue<int> bfs;
                    bfs.push(id);
                    while (!bfs.empty()) {
                        int cur = bfs.front();
                        bfs.pop();
                        int cm = cur % 2;
                        int cell = cur / 2;
                        int cr = cell / m;
                        int cc = cell % m;
                        for (int d = 0; d < 4; d++) {
                            int nr = cr + dr[d];
                            int nc = cc + dc[d];
                            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                                continue;
                            }
                            if (!active(nr, nc, cm)) {
                                continue;
                            }
                            int nid = (nr * m + nc) * 2 + cm;
                            if (comp[nid] == -1) {
                                comp[nid] = cnt;
                                bfs.push(nid);
                            }
                        }
                        if (g[cr][cc] == '.') {
                            int nid = cell * 2 + (1 - cm);
                            if (comp[nid] == -1) {
                                comp[nid] = cnt;
                                bfs.push(nid);
                            }
                        }
                    }
                    cnt++;
                }
            }
        }

        while (q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            int from = comp[(rs * m + cs) * 2];
            int toBlue = comp[(re * m + ce) * 2];
            int toRed = comp[(re * m + ce) * 2 + 1];
            if (from == toBlue || from == toRed) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}
