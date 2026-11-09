#include <bits/stdc++.h>
typedef long long ll;
ll f(const std::vector<std::vector<ll>>&adj,ll k,ll m) {
    std::unordered_map<ll,ll>cnt;std::queue<std::pair<ll,ll>>q;std::vector<ll>vals;
    q.push({0,0});
    while(!q.empty()){
        auto[u,lvl]=q.front();
        q.pop();
        if(lvl>0)cnt[lvl]++;
        for(ll v:adj[u])q.push({v,lvl+1});
    }
    for(auto[lvl,c]:cnt)vals.push_back(std::min(c, k));
    std::sort(vals.begin(),vals.end(),std::greater<ll>());
    ll r=0,lim=std::min(m,static_cast<ll>(vals.size()));
    for(ll i=0;i<lim;i++)r+=vals[i];
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