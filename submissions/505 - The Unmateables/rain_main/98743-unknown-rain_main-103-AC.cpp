#include <bits/stdc++.h>
#include <iomanip>
#include <queue>
using namespace std;
using ll=long long;
using db=double;
const ll N=40005;
const ll M=1000'005;
const ll MOD=1e9+7;
const ll INF=1e18;
using pr=pair<ll,ll>;
using tp=tuple<ll,ll,ll>;

void solve(){
    ll n,k;cin >> n >> k;    
    map<ll,vector<ll>>x,y;
    
    for (int i = 0; i < n; i++) {
        ll a,b,c; char s; cin >> a >> b >> c >> s;
        ll p =a+b;
        if(s=='E') x[p].push_back(a);        
        else y[p].push_back(a);        
    }    
    ll pr=0;    
    for (auto& [s, xv] : x) {
        if (y.find(s) == y.end()) continue;
        auto& yv = y[s];
        sort(yv.begin(), yv.end());        
        for(ll i:xv){
            auto it1=lower_bound(yv.begin(), yv.end(), i);
            auto it2=upper_bound(yv.begin(), yv.end(), i+k-1);
            pr+=distance(it1, it2);
        }
    }
    cout << n*k-pr << "\n";
}
 


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
}