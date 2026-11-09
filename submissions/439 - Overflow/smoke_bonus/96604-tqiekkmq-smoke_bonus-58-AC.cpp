#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    ll r;
    cin >> n >> r;

    ll f0 = 0, f1 = 0; // f[i-2], f[i-1]
    bool ok = true;

    for (int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        if (i >= 2 && a < f0) ok = false;

        ll cur = max(a, f1) + r;
        f0 = f1;
        f1 = cur;
    }

    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}