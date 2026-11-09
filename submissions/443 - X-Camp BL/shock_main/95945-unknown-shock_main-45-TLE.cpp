#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int n, m, q, w;
    if (!(cin >> n >> m >> q)) return;
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for (int i = 0; i < q; i++) {
        ll r, c, p; cin >> r >> c >> p;
        ll p21 = p * p + 1;
        for (ll dr = -p; dr <= p; dr++) {
            ll cur_r = r + dr;
            if (cur_r < 0 || cur_r >= n) continue;
            ll dr2 = dr * dr;
            for (ll dc = -p; dc <= p; dc++) {
                ll cur_c = c + dc;
                if (cur_c < 0 || cur_c >= m) continue;
                ll dist2 = dr2 + dc * dc;
                ll wtf = p21 - dist2;
                if (wtf > 0) {
                    grid[cur_r][cur_c] = wtf;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << (j == m - 1 ? "" : " ");
        }
        cout << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
}