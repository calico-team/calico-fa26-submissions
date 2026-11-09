#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
int find(vector<int>& f, int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> Q(q);
    for (auto& [r, c, p] : Q) cin >> r >> c >> p;
    vector<int> ans(n * m, 0), f(n * m + 1);
    iota(f.begin(), f.end(), 0);
    for (int i = q - 1; i >= 0; --i) {
        auto [R, C, P] = Q[i];
        int P2 = P * P;
        for (int dr = -P; dr <= P; ++dr) {
            int r = R + dr;
            int rem = P2 - dr * dr;
            int W = sqrt(rem); 
            int end_idx = r * m + C + W;
            for (int curr = find(f, r * m + C - W); curr <= end_idx; curr = find(f, curr)) {
                int c = curr % m;
                ans[curr] = rem - (c - C) * (c - C) + 1;
                f[curr] = curr + 1; 
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i * m + j] << (j == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    if (cin >> t) while (t--) solve();
    return 0;
}