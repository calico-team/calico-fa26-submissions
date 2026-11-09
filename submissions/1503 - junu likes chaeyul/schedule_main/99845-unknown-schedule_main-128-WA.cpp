#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD=1e9+7,MAXF=2000005,INF=1e18,INV=5e8+4;


void solve(){
    int n,m,k;cin>>n>>m>>k;
    vector<int> p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    vector<vector<int>> adj(n+1);
    vector<int> root;
    for(int i=1;i<=n;i++){
        if(p[i-1]==0) root.push_back(i);
        else adj[p[i-1]].push_back(i);
    }
    vector<int> ord=root;
    for(int i=0;i<ord.size();i++){
        for(auto v:adj[ord[i]]) ord.push_back(v);
    }
    //max height
    vector<int> dp(n+1,1);
    for(int i=ord.size()-1;i>=0;i--){
        for(auto v:adj[ord[i]]) dp[ord[i]]=max(dp[ord[i]],dp[v]+1);
    }
    
    queue<pair<int,int>> q;
    for(auto u:root){
        q.push({dp[u],u});
    }


    int ans=0;
    //uhhhhhhhhh
    // pq type stuff
    for(int i=0;i<m;i++){
        if(q.empty()) break;
        vector<int> used;
        for(int j=0;j<k;j++){
            if(q.empty()) break;
            int u=q.front().second;
            q.pop();
            used.push_back(u);
            ans++;
        }
        for(auto u:used){
            for(auto v:adj[u]) q.push({dp[v],v});
        }
    }
    cout<<ans<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin>>t;
    while(t--) solve();

}