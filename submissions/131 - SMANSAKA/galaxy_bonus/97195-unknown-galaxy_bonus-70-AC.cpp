#include <bits/stdc++.h>
#define ll long long
using namespace std;

// n cuma 200, aman lah O(NM) precalc buat komponen terhubung

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m,q;
        cin >> n>> m>> q;
        vector<string> g(n);
        for (int i = 0; i <n; i++) cin>> g[i];

        auto get_id = [&](int r, int c, int md) {
            return (r * m +c) * 2 + md;
        };

        int total_nodes =n * m * 2;
        vector<int> comp(total_nodes, -1);
        int cid =0;

        for (int i = 0; i < n; i++) {
            for (int j =0; j < m; j++) {
                for (int md =0; md < 2; md++) {
                    char ch= g[i][j];
                    bool valid = false;
                    if (md ==0 && (ch == '.' || ch == 'B'))valid = true;
                    if (md == 1 && (ch == '.' || ch == 'R')) valid = true;
                    if (!valid) continue;

                    int u = get_id(i, j, md);
                    if (comp[u] !=-1) continue;

                    queue<int> Q;
                    Q.push(u);
                    comp[u] =cid;

                    while (!Q.empty()) {
                        int curr =Q.front();
                        Q.pop();

                        int cr =curr / 2 / m;
                        int cc =(curr / 2) % m;
                        int cmd =curr % 2;

                        int dr[] = {-1,1, 0,0};
                        int dc[] = {0, 0,-1, 1};
                        for (int k = 0; k <4; k++) {
                            int nr = cr + dr[k], nc = cc + dc[k];
                            if (nr < 0 || nr >=n || nc < 0 ||nc >= m) continue;
                            char nch = g[nr][nc];
                            bool nvalid = false;
                            if (cmd == 0&& (nch == '.' || nch == 'B')) nvalid = true;
                            if (cmd == 1 && (nch == '.' || nch == 'R')) nvalid = true;
                            if (!nvalid) continue;

                            int nxt = get_id(nr, nc, cmd);
                            if (comp[nxt]== -1) {
                                comp[nxt] = cid;
                                Q.push(nxt);
                            }
                        }

                        // Spin action di tile normal
                        if (g[cr][cc] == '.') {
                            int nxt_md = 1 - cmd;
                            int nxt = get_id(cr, cc, nxt_md);
                            if (comp[nxt]== -1) {
                                comp[nxt] = cid;
                                Q.push(nxt);
                            }
                        }
                    }
                    cid++;
                }
            }
        }


        while (q--) {
            int r1, c1,r2, c2;
            cin >> r1 >> c1 >>r2 >> c2;

            int start_node = get_id(r1, c1, 0); // start in blue mode
            char end_ch = g[r2][c2];

            bool ok = false;
            if (end_ch == 'B') {
                int target = get_id(r2, c2, 0);
                if (comp[start_node] != -1 && comp[start_node] == comp[target]) ok = true;
            } else if (end_ch =='R') {
                int target = get_id(r2, c2, 1);
                if (comp[start_node] != -1 && comp[start_node] == comp[target]) ok = true;
            } else {
                int t0 =get_id(r2, c2, 0);
                int t1 = get_id(r2, c2, 1);
                if (comp[start_node] != -1 && (comp[start_node] == comp[t0] || comp[start_node] == comp[t1])) ok = true;
            }

            if (ok) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}