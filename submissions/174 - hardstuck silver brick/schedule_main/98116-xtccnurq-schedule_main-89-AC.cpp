#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll dfs(ll i,vector<ll> adj[],vector<ll> &sub_size){
    ll curr=1;
    for(ll v:adj[i]){
        curr+=dfs(v,adj,sub_size);
    }
    return sub_size[i]=curr;
}

int main() {
    ll t;
    cin>>t;
    while(t--){
        ll n,m,k;
        cin>>n>>m>>k;
        ll prereq[n+1];
        for(ll i=1;i<=n;i++)cin>>prereq[i];

        vector<int> roots;
        vector<ll> adj[n+1];

        for(ll i=1;i<=n;i++){
            ll p=prereq[i];
            if (p!=0)adj[p].push_back(i);
            else{
                roots.push_back(i);
            }
        }

        vector<ll> sub_size(n+1);
        for(ll i:roots){
            ll a=dfs(i,adj,sub_size);
        }

        priority_queue<pair<ll,ll>> curr;
        for(ll i:roots)curr.push({sub_size[i],i});

        ll res=0;

        for(ll i=0;i<m;i++){
            if(curr.empty())break;

            ll this_sem=min(k,(ll)curr.size());
            vector<ll> completed;
            for(ll i=0;i<this_sem;i++){
                ll a=curr.top().second;
                curr.pop();
                completed.push_back(a);
                res++;
            }
            for(ll a:completed)
                for(ll v:adj[a])curr.push({sub_size[v],v});
        }
        cout<<res<<endl;
    }
}
