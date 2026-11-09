#include <bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
template <class TT>
using vc=vector<TT>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m, k;
        cin >> n >> m >> k;
        vc<vc<int>> adj(n+1);
        vc<int> fa(n+1);
        for(int i=1;i <= n;i++){
            int v;
            cin >> v;
            adj[v].push_back(i);
            fa[i]=v;
        }
        vc<int> md(n+1);
        auto dfs=[&](auto&& dfs, int u)->void
        {
            for(int v : adj[u]){
                dfs(dfs, v);
                md[u]=max(md[u], md[v]+1);
            }
        };
        dfs(dfs, 0);
        priority_queue<pair<int, int>> can_use, n_use;
        for(int i=1;i <= n;i++){
            if(fa[i] == 0) can_use.push({md[i], i});
        }
        int ans=0;
        for(int i=1;i <= m;i++){
            int cnt=0;
            while(!can_use.empty() && cnt < k){
                ans++;
                cnt++;
                int u=can_use.top().sec;
                can_use.pop();
                for(int x : adj[u]){
                    n_use.push({md[x], x});
                }
            }
            while(!n_use.empty()){
                can_use.push(n_use.top());
                n_use.pop();
            }
        }
        cout << ans << "\n";
    }
}