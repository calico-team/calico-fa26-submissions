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
    priority_queue<a2> pq;
    for(int i=0;i<n;i++){
        if(a[i]==-1){
            pq.push(a2{adj[i].size(),i});
        }
    }
    int ans=0;
    for(int _=0;_<m;_++){
        vector<int> r;
        int sz=pq.size();
        for(int j=0;j<min(sz,k);j++){
            auto [x,i]=pq.top();
            ans++;
            pq.pop();
            r.push_back(i);
        }
        for(int x:r){
            for(int y:adj[x]){
                pq.push(a2{adj[y].size(),y});
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