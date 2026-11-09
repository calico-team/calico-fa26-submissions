#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<long long>> grid(n, vector<long long>(m, 0));
        while (q--) {
            int R, C; long long P;
            cin >> R >> C >> P;
            long long P2 = P * P;
            for (int r = max(0LL, R - P); r <= min((long long)n - 1, R + P); ++r) {
                long long dr2 = (r - R) * (r - R);
                for (int c = max(0LL, C - P); c <= min((long long)m - 1, C + P); ++c) {
                    long long ds = dr2 + (c - C) * (c - C);
                    if (ds <= P2) grid[r][c] = P2 - ds + 1;
                }
            }
        }
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) cout << grid[r][c] << (c == m - 1 ? "" : " ");
            cout << "\n";
        }
    }
    return 0;
}
```[cite: 2, 3]