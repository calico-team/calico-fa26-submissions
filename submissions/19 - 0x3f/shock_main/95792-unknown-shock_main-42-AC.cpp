#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> par;

int find(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        ll n, m;
        int q;
        cin >> n >> m >> q;
        vector<ll> R(q), C(q), P(q);
        for (int i = 0; i < q; i++) cin >> R[i] >> C[i] >> P[i];

        int w = m + 1;
        par.resize(n * w);
        for (int i = 0; i < n * w; i++) par[i] = i;
        vector<ll> ans(n * m, 0);

        for (int k = q - 1; k >= 0; k--) {
            ll p = P[k];
            for (ll r = max(0LL, R[k] - p); r <= min(n - 1, R[k] + p); r++) {
                ll dr = r - R[k];
                ll rem = p * p - dr * dr;
                ll d = sqrtl(rem);
                while (d * d > rem) d--;
                while ((d + 1) * (d + 1) <= rem) d++;

                ll lo = max(0LL, C[k] - d), hi = min(m - 1, C[k] + d);
                if (lo > hi) continue;
                int base = r * w;
                for (int c = find(base + lo) - base; c <= hi; c = find(base + c) - base) {
                    ll dc = c - C[k];
                    ans[r * m + c] = rem - dc * dc + 1;
                    par[base + c] = base + c + 1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j) cout << ' ';
                cout << ans[i * m + j];
            }
            cout << '\n';
        }
    }
    return 0;
}
