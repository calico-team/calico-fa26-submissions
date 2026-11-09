// SAY REX

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ul = unsigned long;
using ld = long double;


void solve() {
    ll n, k;
    cin >> n >> k;
    vector<vector<ll>> diagonals_e(100009), diagonals_n(100009);
    for (ll i = 0; i < n; ++i) {
        ll x, y, z;
        char d;
        cin >> x >> y >> z;
        cin >> d;
        if (d == 'E') {
            diagonals_e[x+y].push_back(x);
        }
        else {
            diagonals_n[x+y].push_back(x);
        }
    }

    ll cnt = 0;
    for (ll i = 0; i < 100009; ++i) {
        if (diagonals_n.size() == 0 || diagonals_e.size() == 0) {
            continue;
        }
        sort(diagonals_n[i].begin(), diagonals_n[i].end());
        for (ll x: diagonals_e[i]) {
            ll start = x - k + 1;
            ll end = x + k - 1;
            auto it1 = lower_bound(diagonals_n[i].begin(), diagonals_n[i].end(), start);
            auto it2 = upper_bound(diagonals_n[i].begin(), diagonals_n[i].end(), end);
            cnt += distance(it1, it2);
        }
    }

    cout << (n * k - cnt) << '\n';
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}
