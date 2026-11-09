#include <bits/stdc++.h>
using namespace std;

bool ok(int r, int c, int md, const vector<string>& g) {
    if (g[r][c] == '.') return true;
    if (g[r][c] == 'B') return md == 0;
    return md == 1;
}

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    
    int sz = 2 * n * m;
    vector<int> comp(sz, -1);
    int cnt = 0;
    
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};
    
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            for (int md = 0; md < 2; md++) {
                if (!ok(r, c, md, g)) continue;
                int id = (r * m + c) * 2 + md;
                if (comp[id] != -1) continue;
                
                vector<int> st = {id};
                comp[id] = cnt;
                
                while (!st.empty()) {
                    int cur = st.back();
                    st.pop_back();
                    int cm = cur % 2;
                    int cell = cur / 2;
                    int cr = cell / m, cc = cell % m;
                    
                    for (int d = 0; d < 4; d++) {
                        int nr = cr + dr[d], nc = cc + dc[d];
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (!ok(nr, nc, cm, g)) continue;
                        int nid = (nr * m + nc) * 2 + cm;
                        if (comp[nid] == -1) {
                            comp[nid] = cnt;
                            st.push_back(nid);
                        }
                    }
                    
                    if (g[cr][cc] == '.') {
                        int nid = cell * 2 + (cm ^ 1);
                        if (comp[nid] == -1) {
                            comp[nid] = cnt;
                            st.push_back(nid);
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
        int sid = (rs * m + cs) * 2;
        int em = (g[re][ce] == 'R') ? 1 : 0;
        int eid = (re * m + ce) * 2 + em;
        if (comp[sid] != -1 && comp[sid] == comp[eid]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
