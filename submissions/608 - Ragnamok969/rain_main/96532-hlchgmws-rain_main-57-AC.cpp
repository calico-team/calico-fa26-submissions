#include<bits/stdc++.h>
using namespace std;

#define ll long long
void solve() {
    int n; ll k; cin >> n >> k;
    vector<ll> x(n+1), y(n+1), z(n+1);
    vector<char> d(n+1);

    set<ll> ls;
    map<ll, vector<ll>> xn, xe;
    for(int i=1;i<=n;i++) {
        cin >> x[i] >> y[i] >> z[i] >> d[i];
        if(d[i] == 'E') xe[x[i] + y[i]].push_back(x[i]);
        else xn[x[i] + y[i]].push_back(x[i]);
    
        ls.insert(x[i] + y[i]);
    }

    for(auto &[i, j] : xn) sort(j.begin(), j.end());
    for(auto &[i, j] : xe) sort(j.begin(), j.end());
    
    ll ans = n * k;
    for(auto &i:ls) {
        if(xn.find(i) == xn.end() || xe.find(i) == xe.end()) continue;
        
        for(auto &j:xe[i]) {
            ll l = lower_bound(xn[i].begin(), xn[i].end(), j) - xn[i].begin();
            ll r = upper_bound(xn[i].begin(), xn[i].end(), j + k - 1) - xn[i].begin() - 1;
            
            ans -= max(r-l+1, 0ll);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 1; cin >> t;
    while(t--) solve();
}