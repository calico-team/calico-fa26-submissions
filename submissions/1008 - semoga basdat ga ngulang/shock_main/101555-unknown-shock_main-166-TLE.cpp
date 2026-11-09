#include <bits/stdc++.h>
using namespace std;

#define abysr ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define vll vector<long long>
#define endl "\n"

int main() {

    abysr

    ll t;
    cin >> t;

    while (t--) {
        ll n, m, q;
        cin >> n >> m >> q;

        vector<vector<ll>> ans(n, vector<ll>(m, 0));
        vector<vector<bool>> vis(n, vector<bool>(m, 0));

        vector<tuple<ll, ll, ll>> vec(q);

        for (ll i = 0; i < q; i++) {
            ll r, c, p;
            cin >> r >> c >> p;

            vec[i] = {r, c, p};
        }

        for (ll i = q - 1; i >= 0; i--) {
            auto [R, C, P] = vec[i];

            for (ll r = R - P; r <= R + P; r++) {
                ll dr = r - R;
                ll d = sqrtl(P * P - dr * dr);

                for (ll c = C - d; c <= C + d; c++) {

                    if (vis[r][c]) continue;

                    ll dc = c - C;
                    ll s = P * P - dr * dr - dc * dc + 1;

                    if (s > 0) {
                        ans[r][c] = s;
                        vis[r][c] = 1;
                    }
                }
            }
        }

        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                cout << ans[i][j] << (j == m - 1 ? '\n' : ' ');
            }
        }
    }

    return 0;
}