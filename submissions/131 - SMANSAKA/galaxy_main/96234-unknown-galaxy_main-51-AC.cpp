#include <bits/stdc++.h>
#define ll long long

using namespace std;

int get_idx(int r,int c, int mode, int m) {
    return (r * m +c) * 2 +mode;
}

void solve() {
    int n, m, q;
    if (!(cin >> n >> m>> q)) return;
    
    vector<string> g(n);
    for (int i = 0; i <n; ++i) cin >> g[i];
    
    vector<int> comp(2 * n * m, -1);
    int cid = 0;
    int dr[] = {-1, 1,0,0};
    int dc[] = {0, 0,-1, 1};
    
    // bismillah ga ada corner case nyasar
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int mode = 0; mode < 2; ++mode) {
                int u = get_idx(i, j, mode, m);
                if (comp[u] != -1) continue;
                if (mode ==0 && g[i][j] == 'R') continue;
                if (mode ==1 && g[i][j] == 'B') continue;
                
                queue<int> qu;
                qu.push(u);
                comp[u] = cid;
                
                while (!qu.empty()) {
                    int cur = qu.front(); qu.pop();
                    int cr =cur / 2 / m;
                    int cc = (cur / 2) % m;
                    int cm =cur % 2;
                    
                    if (g[cr][cc]== '.') {
                        int nxt_m =1 - cm;
                        int nxt = get_idx(cr, cc, nxt_m, m);
                        if (comp[nxt]== -1) {
                            comp[nxt] = cid;
                            qu.push(nxt);
                        }
                    }
                    
                    for (int d =0; d < 4; ++d) {
                        int nr = cr + dr[d];
                        int nc= cc + dc[d];
                        if (nr <0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (cm == 0 && g[nr][nc] == 'R') continue;
                        if (cm == 1 && g[nr][nc] == 'B') continue;
                        
                        int nxt =get_idx(nr, nc, cm, m);
                        if (comp[nxt] ==-1) {
                            comp[nxt] =cid;
                            qu.push(nxt);
                        }
                    }
                }
                cid++;
            }
        }
    }
    
    // aman, pake connected component biar O(NM + Q) ga TLE
    while (q--) {
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;
        
        int st = get_idx(rs, cs, 0, m);
        int st_c = comp[st];
        
        int ed1 = (g[re][ce] != 'R') ? comp[get_idx(re, ce, 0, m)] : -1;
        int ed2 = (g[re][ce] != 'B') ? comp[get_idx(re, ce, 1, m)] : -1;
        
        if ((ed1 != -1 && ed1 == st_c) || (ed2 != -1 && ed2 == st_c)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    // buru-buru euy sisa 5 menit lagi
    return 0;
}