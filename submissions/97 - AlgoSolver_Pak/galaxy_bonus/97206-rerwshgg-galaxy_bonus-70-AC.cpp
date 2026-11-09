#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m, Q;
        cin >> n >> m >> Q;
        vector<string> g(n);
        for (int i = 0; i < n; i++) cin >> g[i];

        vector<int> rs(Q), cs(Q), re(Q), ce(Q);
        for (int i = 0; i < Q; i++) {
            cin >> rs[i] >> cs[i] >> re[i] >> ce[i];
        }

        int total = 2 * n * m;
        vector<int> comp(total, -1);

        auto id = [&](int mode, int r, int c) {
            return mode * n * m + r * m + c;
        };

        auto active = [&](int mode, int r, int c) {
            char ch = g[r][c];
            if (ch == '.') return true;
            if (ch == 'R') return mode == 1;
            if (ch == 'B') return mode == 0;
            return false;
        };

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        int curComp = 0;
        queue<int> q;

        for (int mode = 0; mode < 2; mode++) {
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    int start = id(mode, r, c);
                    if (comp[start] != -1) continue;
                    if (!active(mode, r, c)) {
                        comp[start] = -2;
                        continue;
                    }
                    comp[start] = curComp;
                    q.push(start);
                    while (!q.empty()) {
                        int cur = q.front(); q.pop();
                        int cmode = cur / (n * m);
                        int rem = cur % (n * m);
                        int cr = rem / m;
                        int cc = rem % m;

                        // spin: sirf normal tile pe mode badlo
                        if (g[cr][cc] == '.') {
                            int nid = id(1 - cmode, cr, cc);
                            if (comp[nid] == -1) {
                                comp[nid] = curComp;
                                q.push(nid);
                            }
                        }
                        // 4 taraf chalo
                        for (int d = 0; d < 4; d++) {
                            int nr = cr + dr[d];
                            int nc = cc + dc[d];
                            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                            if (!active(cmode, nr, nc)) continue;
                            int nid = id(cmode, nr, nc);
                            if (comp[nid] == -1) {
                                comp[nid] = curComp;
                                q.push(nid);
                            }
                        }
                    }
                    curComp++;
                }
            }
        }

        for (int i = 0; i < Q; i++) {
            int s = id(0, rs[i], cs[i]);
            int e1 = id(0, re[i], ce[i]);
            int e2 = id(1, re[i], ce[i]);
            if (comp[s] != -1 && comp[s] != -2 &&
                (comp[s] == comp[e1] || comp[s] == comp[e2])) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}