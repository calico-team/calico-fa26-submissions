#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ll t;
    cin>>t;
    while(t--){
        ll n,m,k;
        cin>>n>>m>>k;
        ll prereq[n+1];
        for(ll i=1;i<=n;i++)cin>>prereq[i];

        priority_queue<ll> curr;
        vector<ll> adj[n+1];

        for(ll i=1;i<=n;i++){
            ll p=prereq[i];
            if (p!=0)adj[p].push_back(i);
            else curr.push(i);
        }

        ll res=0;

        for(ll i=0;i<m;i++){
            if(curr.empty())break;

            ll this_sem=min(k,(ll)curr.size());
            vector<ll> completed;
            for(ll i=0;i<this_sem;i++){
                ll a=curr.top();
                curr.pop();
                completed.push_back(a);
                res++;
            }
            for(ll a:completed)
                for(ll v:adj[a])curr.push(v);
        }
        cout<<res<<endl;
    }
}
