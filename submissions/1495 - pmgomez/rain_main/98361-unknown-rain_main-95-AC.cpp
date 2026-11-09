#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll XMAX = 1E5;

struct drone {
    ll x,y,z;
    bool up=1;
};
void solve(){
    ll N,K;cin>>N>>K;
    vector<drone> drones(N);
    for (ll i=0;i<N;i++){
        ll x,y,z; cin>>x>>y>>z;
        char d; cin >> d;
        drones[i] = {x,y,z,d=='N'};
    }
    map<ll,set<ll>> right;
    vector<pair<ll,ll>> check;
    for (ll i=0;i<N;i++){
        auto [ x, y, z, d ] = drones[i];
        ll k=x+y;
        if (d){
            check.push_back({k,y});
        }
        else{
            right[k].insert(y);
        }
    }
    ll ans = N*K;
    for (auto [k,y] : check){
        auto& tocheck = right[k];
        auto upperit = tocheck.upper_bound(y+K-1);
        auto lowerit = tocheck.lower_bound(y);
        ll cnt = distance(lowerit,upperit);
        ans -= cnt;
    }
    cout << ans << endl;
    
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}