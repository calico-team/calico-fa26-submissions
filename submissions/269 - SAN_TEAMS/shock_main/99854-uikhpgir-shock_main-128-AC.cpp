#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct DSU {
    vector<ll> parent;
    DSU(ll n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    ll find(ll x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
};
struct Earthquake {
    ll r, c, p;
};
int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, m, q;
        cin >> n >> m >> q;
        vector<Earthquake> a(q);
        for (ll i = 0; i < q; i++) {
            cin >> a[i].r >> a[i].c >> a[i].p;
        }
        vector<ll> ans(n * m, 0);
        DSU dsu(n * m);
        for (ll i = q - 1; i >= 0; i--) {
            auto [r, c, p] = a[i];
            for (ll dr = -p; dr <= p; dr++) {
                ll row = r + dr;
                ll rem = p * p - dr * dr;
                ll d = sqrtl(rem);
                while ((d + 1) * (d + 1) <= rem) d++;
                while (d * d > rem) d--;
                ll L = row * m + c - d;
                ll H = row * m + c + d;
                ll x = dsu.find(L);
                while (x <= H) {
                    ll col = x % m;
                    ll dc = col - c;
                    ans[x] = p*p - dr*dr - dc*dc + 1;
                    dsu.parent[x] = dsu.find(x + 1);
                    x = dsu.parent[x];
                }
            }
        }
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                if (j) cout << " ";
                cout << ans[i * m + j];
            }
            cout << "\n";
        }
    }
}