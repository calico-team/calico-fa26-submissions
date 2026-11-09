#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<vector<int>> adj;
vector<int> h;

int dfs(int u){
    h[u] = 1;

    for(int v : adj[u]) 
        h[u] = max(h[u], dfs(v) + 1);
        
    return h[u];
}

void solve(){
    int n, m, k, ans =0; cin >> n >> m >> k;

    adj.resize(n+1); h.resize(n+1);

    for(int i = 1; i <= n; ++i){
        int p; cin >> p;
        adj[p].push_back(i);
    }

    dfs(0); // initially

    priority_queue<pair<int,int>> pq; //choose with largest stack height cuz opens free slots? js greedy i think

    for(int v : adj[0]) 
        pq.push(make_pair(h[v],v));

    int j;

    vector<int> done;

    //update over all m semesters
    while(!pq.empty() && m--){
        done.clear();

        while(!pq.empty() && done.size() < k){
            j = pq.top().second;

            done.push_back(j); 
            pq.pop();
        }

        ans += done.size();

        for(int u : done){
            for(int v : adj[u]) 

            pq.push(make_pair(h[v-1],v));
        }
    }

    cout << ans << "\n";
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1; cin >> t;

    while(t--){
        adj.clear(); h.clear();

        solve();
    }

}