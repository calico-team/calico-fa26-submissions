#include<bits/stdc++.h>
using namespace std;
#define int long long
#define a2 array<int,2>
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> a(n);
    vector<vector<int>> adj(n);
    for(int& x:a){
        cin>>x;
        x--;
    }
    for(int i=0;i<n;i++){
        if(a[i]==-1) continue;
        adj[a[i]].push_back(i);
    }
    vector<int> sz(n);
    function<void(int)> dfs=[&](int i){
        sz[i]=1;
        for(int j:adj[i]){
            dfs(j);
            sz[i]+=sz[j];
        }
    };
    priority_queue<a2> pq;
    for(int i=0;i<n;i++){
        if(a[i]==-1){
            dfs(i);
            pq.push({sz[i],i});
        }
    }
    int ans=0;
    for(int _=0;_<m;_++){
        vector<int> r;
        int s=pq.size();
        for(int j=0;j<min(s,k);j++){
            auto [x,i]=pq.top();
            ans++;
            pq.pop();
            r.push_back(i);
        }
        for(int x:r){
            for(int y:adj[x]){
                pq.push({sz[y],y});
            }
        }
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}