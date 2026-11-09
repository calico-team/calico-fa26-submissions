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
    int n, k ;
    cin>> n >>k;

    vector<char> v(k);
    for(int i= 0; i < k; i++) {
        cin >> v[i];
    }
    // store indices we still don know
    vector<int> rem;
    for(int i =0; i< n; i++) {
        rem.pb(i);
    }
    string cur_s(n, '.');
    int done = 0;

    for(int step= 0; step < k; step++) {
        if(done) break ;

        char ch = v[step];

        // try putting this char
        for(int i= 0; i < sz(rem); i++) {
            cur_s[rem[i]] = ch;
        }
        cout <<cur_s << endl;
        cout.flush();

        string rep;
        cin >>rep;

        if(rep == "CORRECT" ) {
            done = 1;
            continue;
        }
        // filter out spots
        vector<int> nxt_rem;
        for(int i =0; i < sz(rem); i++) {
            int idx = rem[i];
            if(rep[idx] == '_') {
                nxt_rem.pb(idx);
            }
            else {
                cur_s[idx] = rep[idx];
            }
        }
        rem = nxt_rem;
    }
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