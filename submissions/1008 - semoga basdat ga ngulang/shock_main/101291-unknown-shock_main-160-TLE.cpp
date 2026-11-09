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

        for (ll i = 0; i < q; i++) {
            ll R, C, P;
            cin >> R >> C >> P;

            for (ll r = R - P; r <= R + P; r++) {
                for (ll c = C - P; c <= C + P; c++) {

                    ll dr = r - R;
                    ll dc = c - C;

                    ll s = P * P - dr * dr - dc * dc + 1;

                    if (s > 0) {
                        ans[r][c] = s;
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