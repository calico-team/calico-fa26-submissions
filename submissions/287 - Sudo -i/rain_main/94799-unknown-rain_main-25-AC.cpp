#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;

void solve(){
    ll n,k,x,y,z;
    char d[10];
    vector<pair<ll,ll>> nor;
    map<ll,vector<ll>> east;
    scanf("%lld %lld",&n,&k);
    for(ll i=0; i<n; i++){
        scanf("%lld %lld %lld %s",&x,&y,&z,d);
        if(d[0]=='E') east[x+y].push_back(x);
        else nor.push_back({x,y});
    }
    for(auto &[s,v]:east) sort(v.begin(),v.end());
    ll res=n*k;
    for(auto [x,y]:nor){
        if(!east.count(x+y)) continue;
        auto &t=east[x+y];
        res-=lower_bound(t.begin(),t.end(),x)-lower_bound(t.begin(),t.end(),x-k+1);
    }
    printf("%lld\n",res);
}

int main(){
    //freopen("p4.in","r",stdin);
    //freopen("p4.out","w",stdout);
    ll t;
    scanf("%lld",&t);
    while(t--) solve();
    return 0;
}