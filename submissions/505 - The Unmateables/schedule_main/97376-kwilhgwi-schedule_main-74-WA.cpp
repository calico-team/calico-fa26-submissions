#include <bits/stdc++.h>
typedef long long ll;
ll f(const std::vector<std::vector<ll>>&adj,ll k,ll m) {
    std::unordered_map<ll,ll>cnt;std::queue<std::pair<ll,ll>>q;ll r=0;
    q.push({0,0});
    while(!q.empty()){
        auto[u,lvl]=q.front();
        q.pop();
        if(lvl>0)cnt[lvl]++;
        for(ll v:adj[u])q.push({v,lvl+1});
    }
    for(ll i=1;i<=m;i++)if(cnt.count(i))r+=std::min(cnt[i],k);
    return r;
}
int main() {
    std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    short t;std::cin>>t;
    while(t--){
        ll n,m,k;std::cin>>n>>m>>k;
        std::vector<ll>p(n+1);std::vector<std::vector<ll>>adj(n+1);
        for(ll i=1;i<=n;i++){std::cin>>p[i];adj[p[i]].push_back(i);}
        std::cout<<f(adj,k,m)<<'\n';
    }
}
