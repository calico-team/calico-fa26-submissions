#include <bits/stdc++.h>
using namespace std;

#define abysr ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define vll vector<long long>
#define endl "\n"

int find(int r, int x, vector<vector<int>> &par) {
    int y = x;

    while (par[r][y] != y) {
        y = par[r][y];
    }

    while (par[r][x] != x) {
        int z = par[r][x];
        par[r][x] = y;
        x = z;
    }

    return y;
}

int main() {

    abysr

    ll t;
    cin >> t;

    while (t--) {
        ll n, m, q;
        cin >> n >> m >> q;

        vector<vector<ll>> ans(n, vector<ll>(m, 0));

        vector<tuple<ll, ll, ll>> vec(q);

        for (ll i = 0; i < q; i++) {
            ll r, c, p;
            cin >> r >> c >> p;

            vec[i] = {r, c, p};
        }

        vector<vector<int>> par(n, vector<int>(m + 1));

        for (ll i = 0; i < n; i++) {
            iota(par[i].begin(), par[i].end(), 0);
        }

        for (ll i = q - 1; i >= 0; i--) {
            auto [R, C, P] = vec[i];

            for (ll r = R - P; r <= R + P; r++) {
                ll dr = r - R;
                ll rem = P * P - dr * dr;

                ll d = sqrtl(rem);

                ll l = C - d;
                ll rr = C + d;

                ll c = find(r, l, par);

                while (c <= rr) {
                    ll dc = c - C;

                    ans[r][c] = rem - dc * dc + 1;

                    ll nxt = find(r, c + 1, par);
                    par[r][c] = nxt;

                    c = nxt;
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