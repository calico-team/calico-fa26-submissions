#include <bits/stdc++.h>
#define ll long long
using namespace std;

// panik, pake reverse query + skip cell yang udah ke-update biar O(N*M + Q * P) / amortized
void solve() {
    int n, m,q;
    if (!(cin >> n >> m >>q)) return;

    vector<tuple<int, int, int>> eq(q);
    for (int i = 0; i < q; i++) {
        int r, c, p;
        cin >> r >> c>> p;
        eq[i] = {r, c,p};
    }

    vector<vector<int>> g(n, vector<int>(m, 0));
    
    vector<vector<int>> nxt(n, vector<int>(m + 2, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m + 1; j++) {
            nxt[i][j] = j; // pointer ke kolom unvisited berikutnya
        }
    }

    // Lambda buat find set (path compression sederhana buat skip kolom)
    auto find_col = [&](auto& self, int r_idx, int c_idx) -> int {
        if (nxt[r_idx][c_idx] == c_idx) return c_idx;
        return nxt[r_idx][c_idx] = self(self, r_idx, nxt[r_idx][c_idx]);
    };

    // Jalan dari earthquake terakhir ke pertama!
    for (int i = q - 1; i >= 0; i--) {
        auto [r, c, p] = eq[i];
        int p2 = p * p;
        int r1 = max(0, r -p);
        int r2 = min(n - 1, r +p);
        int c1 = max(0, c - p);
        int c2 = min(m - 1,c +p);

        for (int rr = r1; rr <= r2; rr++) {
            int dr = rr - r;
            int dr2 = dr *dr;
            
            // Lompat-lompat kolom pakai pointer nxt biar yg udah diisi gak dicek lagi
            int cur_c = find_col(find_col, rr, c1);
            while (cur_c <= c2) {
                int dc = cur_c - c;
                if (dr2 + dc * dc <= p2) {
                    g[rr][cur_c] = p2 -(dr2 + dc * dc) + 1;
                    // Tandai kolom ini udah di-handle (pointing ke cur_c + 1)
                    nxt[rr][cur_c] = find_col(find_col, rr, cur_c + 1);
                }
                cur_c = find_col(find_col, rr, cur_c + 1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
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
        while (t--)solve();
    }
    return 0;
}