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
    ll n, r ;
    cin>> n >> r;

    // ust use a tiny static array with l and r pointers
    ll q[5];
    int l = 0, rr = 0;
    int bad = 0;

    for(int i= 0; i < n; i++) {
        ll x;
        cin >>x;

        // still gotta read rest of input
        if(bad ) continue;
        while(l < rr && q[l] <=x) {
            l++;
        }
        int in_q = rr - l;

        if(in_q == 2) {
            bad = 1;
            continue ;
        }
        if(in_q == 0) {
            // reset pointers so it never overflows q[5]
            l = 0;
            rr = 0;
            q[rr++] = x+ r;
        }
        else {
            // 1 battery currently charign
            ll prev = q[l];
            l = 0;
            rr = 0;
            q[rr++] = prev;
            q[rr++] = prev +r;
        }
    }
    if(!bad) cout << "YES" <<endl;
    else cout<< "NO" << endl;
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