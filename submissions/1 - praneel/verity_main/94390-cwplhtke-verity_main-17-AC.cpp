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
    cin >>n >> k;

    vector<char> chs(k);
    for(int i= 0; i < k; i++) {
        cin>> chs[i];
    }
    // track which spots we already figured out
    vector<int> vis(n, 0);
    string ans(n, 'a');
    for(int j =0; j< k; j++) {
        char cur = chs[j];

        for(int i= 0; i < n; i++) {
            if(!vis[i]) {
                ans[i] = cur;
            }
        }

        // need to flush!!
        cout << ans << endl;
        cout.flush();
        string verdict ;
        if(!(cin >>verdict)) exit(0);

        if(verdict == "CORRECT") {
            return ;
        }
        // lock in
        for(int i =0; i <n; i++) {
            if(verdict[i] != '_') {
                vis[i] = 1;
                ans[i] = verdict[i];
            }
        }
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