#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >>q)) return;

    vector<vector<int>> g(n, vector<int>(m, 0));

    for (int i = 0; i < q; i++) {
        int r, c, p;
        cin >> r >> c >>p;
        
        int p2 = p * p;
        int r1 = max(0, r -p);
        int r2 = min(n - 1,r + p);
        int c1 = max(0, c - p);
        int c2 = min(m - 1, c + p);

        for (int rr = r1; rr <= r2; rr++) {
            int dr = rr -r;
            int dr2 = dr * dr;
            // optimasi: hitung sisa kuadrat jarak kolom maksimal
            int max_dc2 = p2 -dr2;
            if (max_dc2 < 0) continue;
            
            int limit = sqrt(max_dc2);
            int cc_start =max(c1, c - limit);
            int cc_end =min(c2,c + limit);

            for (int cc = cc_start; cc <= cc_end; cc++) {
                int dc = cc -c;
                g[rr][cc] = p2 - (dr2 + dc * dc) + 1;
            }
        }
    }
    // cetak pakai stringstream atau buffer biar cepet kalau N*M gede
    for (int i =0; i < n; i++) {
        for (int j =0; j < m; j++) {
            cout << g[i][j] <<(j == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (cin >>t) {
        while (t--) solve();
    }
    return 0;
}