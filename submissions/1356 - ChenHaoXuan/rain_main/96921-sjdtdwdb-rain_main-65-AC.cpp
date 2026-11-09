#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;

void solve()
{
    int nn; ll k; cin>>nn>>k;
    map<ll, vector<ll>>e,n;
    for(int i=0;i<nn;i++){
        ll x, y, z; char d; cin>>x>>y>>z>>d;
        if(d=='E')e[x+y].push_back(x);
        if(d=='N')n[x+y].push_back(x);
    }
    ll ans = 0;
    for(auto u : e){
        auto it = n.find(u.first);
        if(it==n.end())continue;
        sort(it->second.begin(), it->second.end());
        for(auto v:u.second){
            auto lf = lower_bound(it->second.begin(), it->second.end(), v);
            auto rg = upper_bound(it->second.begin(), it->second.end(), v+k-1);
            ans += distance(lf, rg);
        }
    }
    cout << (ll)nn*k-ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}