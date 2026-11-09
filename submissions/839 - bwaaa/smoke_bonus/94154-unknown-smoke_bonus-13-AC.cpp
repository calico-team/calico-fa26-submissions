#include <bits/stdc++.h>

using namespace std;

#define all(v) begin(v), end(v)
using ll = long long;

//const ll MOD = 998244353;
const ll MOD = 1e9+7;

const ll INFL = 1e18;
const int INF = 1e9;

void $() {
    ll n, r;
    cin >> n >> r;
    ll a = 0, b = 0;
    ll prv = 0;
    bool ok = true;
    for (ll i=0; i<n; i++) {
        ll cur;
        cin >> cur;
        ll delta = cur - prv;
        ll x = min(a, delta);
        a -= x;
        delta -= x;
        if (a) {
            ok = false;
        }
        b = max(0ll, b-delta);
        a += r;
        swap(a, b);
        prv = cur;
    }
    if (ok) cout << "YES\n";
    else cout << "NO\n"; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc=1;
    cin >> tc;
    while (tc--) $();
}
