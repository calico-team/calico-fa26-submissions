#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

using namespace std;

const ll MOD = 1e9 + 7;

// just keeping this here in case i need it later
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(a, b % a);
}
void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    if(b < 0) b += MOD;

    while(e) {
        if(e&1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }

    return r;
}
void solve() {
    int n ;
    ll k;
    cin >> n >> k;

    map<ll, vector<ll>> east, north;

    for(int i= 0; i < n; i++) {
        ll x, y, z;
        char d;
        cin>> x >> y >> z >> d;

        ll s = x + y;
        if(d == 'E') {
            east[s].pb(x);
        }
        else {
            north[s].pb(x);
        }
    }
    ll meet = 0;
    for(auto &p : east) {
        ll s = p.first;
        vector<ll> &es = p.second;

        if(north.find(s) == north.end()) continue;
        vector<ll> &ns = north[s];
        sort(all(ns));

        for(int i =0; i< sz(es); i++) {
            ll a = es[i];
            auto l_it = lower_bound(all(ns), a);
            auto r_it = upper_bound(all(ns), a + k - 1);
            meet += (r_it - l_it);
        }
    }
    ll ans = (ll)n * k - meet;
    cout << ans << endl;
}
int main() {
    fastio();

    int T;
    cin >> T;

    while(T--) {
        solve();
    }

    return 0;
}