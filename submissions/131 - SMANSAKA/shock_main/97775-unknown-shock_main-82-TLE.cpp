#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    // grid ukurannya bisa sampai 10^6 total, tapi Q cuma 2 * 10^4
    
    vector<vector<int>> g(n, vector<int>(m, 0));

    for (int i = 0; i <q; i++) {
        int r, c,p;
        cin >> r >>c >> p;

        int r1 =max(0, r - p);
        int r2 =min(n - 1, r + p);
        int c1 =max(0, c - p);
        int c2 =min(m - 1, c + p);

        for (int rr =r1; rr<= r2; rr++) {
            int dr = rr -r;
            int dr2 = dr * dr;
            for (int cc = c1;cc <= c2; cc++) {
                int dc = cc -c;
                if (dr2 + dc *dc <= p * p) {
                    int val = p *p - (dr2 + dc * dc) + 1;
                    g[rr][cc] = val;
                }
            }
        }
    }

    for (int i = 0; i <n; i++) {
        for (int j = 0; j < m; j++) {
            cout << g[i][j] <<(j == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}