#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Quake{
    ll r, c, p;
};

ll search(ll r, ll c, vector<vector<ll>> &ans, vector<vector<ll>> &p) {
    ll f = c;
    while (p[r][f] != f) {f = p[r][f];}
    while (p[r][c] != c) {
        ll curr = p[r][c];
        p[r][c] = f, c = curr;
    }
    return f;
}

int main() {
	ios::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, q; cin >> n >> m >> q;
        vector<Quake> quakes(q);
        for (auto &[r, c, p] : quakes) {
            cin >> r >> c >> p;
        }
        vector<vector<ll>> ans(n, vector<ll>(m));

        vector<vector<ll>> p(n, vector<ll>(m + 1));

        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j <= m; j++) {
                p[i][j] = j;
            }
        }

        for (ll i = q - 1; i >= 0; i--) {
            ll cr = quakes[i].r, cc = quakes[i].c, cp = quakes[i].p;
            for (ll i = cr - cp; i <= cr + cp; i++) {
                ll h = i - cr;
                ll rem = cp * cp - h * h;
                ll d = (ll)sqrt(rem);
                while ((d + 1) * (d + 1) <= rem) {d++;}
                while (d * d > rem) {d--;}

                ll l = cc - d, r = cc + d;
                ll j = search(i, l, ans, p);
                while (j <= r) {
                    ll dc = j - cc;
                    ans[i][j] = rem - dc * dc + 1;
                    p[i][j] = search(i, j + 1, ans, p);
                    j = search(i, j, ans, p);
                }
            }
        }
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                if (j > 0) {cout << " ";}
                cout << ans[i][j];
            }
            cout << "\n";
        }
    }
}
