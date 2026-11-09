#include<bits/stdc++.h>
typedef long long ll;
int main(){
    std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    short t;std::cin>>t;
    while(t--){
		ll n,m,k,r=0;std::cin>>n>>m>>k;
        std::vector<ll>p(n+1),h(n+1,1),o(1);std::vector<std::vector<ll>>a(n+1);std::priority_queue<std::pair<ll,ll>>q;
        for(ll i=1;i<=n;i++)std::cin>>p[i],a[p[i]].push_back(i);
        for(ll i=0;i<o.size();i++)for(ll v:a[o[i]])o.push_back(v);
        for(ll i=n;i>0;i--)h[p[o[i]]]=std::max(h[p[o[i]]],h[o[i]]+1);
        for(ll v:a[0])q.push({h[v],v});
        while((m--)&&(!q.empty())){
            std::vector<ll>s;
            while(s.size()<k&&!q.empty())s.push_back(q.top().second),q.pop();
            r+=s.size();
            for(ll u:s)for(ll v:a[u])q.push({h[v],v});
        }
        std::cout<<r<<'\n';
    }
}