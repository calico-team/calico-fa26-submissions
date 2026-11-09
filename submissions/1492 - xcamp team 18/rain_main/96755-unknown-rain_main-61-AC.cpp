#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll n, k; cin >> n >> k; 
    ll ans = n*k; vector<pair<ll,ll>> edr;
    unordered_map<ll,vector<ll>> ndr; 
    for (ll i = 0; i < n; i++) {
        ll x, y, z; char d;
        cin >> x >> y >> z >> d;
        if (d == 'E') edr.push_back({x,y});
        else ndr[x+y].push_back(x); 
    } for (auto& x : ndr) 
        sort(x.second.begin(), x.second.end());
    for (ll i = 0; i < edr.size(); i++) {
        ll key = edr[i].first+edr[i].second;
        if (ndr.count(key)) { 
            auto it1 = lower_bound(ndr[key].begin(), ndr[key].end(), edr[i].first);
            auto it2 = upper_bound(ndr[key].begin(), ndr[key].end(), edr[i].first+k-1);
            ans -= (it2-it1);
        }
    } cout << ans << endl;
    return;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll T; cin >> T; while (T--) solve();
    return 0;
}
