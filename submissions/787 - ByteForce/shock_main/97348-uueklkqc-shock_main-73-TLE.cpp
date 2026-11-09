#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;
    
    vector<vector<long long>> grid(n, vector<long long>(m, 0));
    
    for (int i = 0; i < q; ++i) {
        int r_epicenter, c_epicenter;
        long long p;
        cin >> r_epicenter >> c_epicenter >> p;
        
        long long p_sq = p * p;
        int row_max_val = n - 1;
        int col_max_val = m - 1;
        
        int row_min = max(0, r_epicenter - (int)p);
        int row_max = min(row_max_val, r_epicenter + (int)p);
        int col_min = max(0, c_epicenter - (int)p);
        int col_max = min(col_max_val, c_epicenter + (int)p);
        
        for (int r = row_min; r <= row_max; ++r) {
            long long dr = r - r_epicenter;
            long long dr_sq = dr * dr;
            for (int c = col_min; c <= col_max; ++c) {
                long long dc = c - c_epicenter;
                long long dist_sq = dr_sq + dc * dc;
                if (dist_sq <= p_sq) {
                    grid[r][c] = p_sq - dist_sq + 1;
                }
            }
        }
    }
    
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cout << grid[r][c] << (c == m - 1 ? "" : " ");
        }
        cout << "\n";
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