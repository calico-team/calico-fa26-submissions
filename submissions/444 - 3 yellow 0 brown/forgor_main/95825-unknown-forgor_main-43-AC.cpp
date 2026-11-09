#include "bits/stdc++.h"
using namespace std;
#define fast ios_base::sync_with_stdio(0) , cin.tie(0)
using ll=long long;
#define MOD 1000001

void solve() {
    string t;
    cin >> t;
    if (t=="FIRST"){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        for (int i =0;i<n-1;i++){
            int u,v;
            cin >>u>>v;
            u--;v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> pars(n,-1);
        auto dfs=[&](int u, auto&&f)->void{
            for (int v : adj[u]){
                if (v!=pars[u]){
                    pars[v]=u;
                    f(v,f);
                }
            }
        };
        dfs(0,dfs);
        int s = 0;
        for (int i =1;i<n;i++){
            cout << pars[i] << " ";
            s=(s+pars[i])%MOD;
        }
        cout << (-s+MOD)%MOD << endl;
    }else{
        int n;
        cin >> n;
        vector<int> ps(n);
        int s= 0;
        for (int i=0;i<n;i++){
            cin >> ps[i];
            if (ps[i]!=-1){
                s=(s+ps[i])%MOD;
            }
        }
        for (int i=0;i<n;i++){
            if (ps[i]==-1){
                ps[i]=(-s+MOD)%MOD;
            }
        }
        for (int i =0;i<n-1;i++){
            cout << i+2 << " " << ps[i]+1 << '\n';
        }
    }
}

signed main() {
    fast;
    int t=1;
    while (t--) solve();
    return 0;
}
