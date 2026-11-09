#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using str = string;

#define int long long
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define fox(i,n) for(int i=0;i<(n);++i)

vector<pii> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


void dfs(int cur, vector<int>& vis, vector<vector<int>>& adj, vector<int>& ans){
    vis[cur] = 1;
    for(int nxt: adj[cur]){
        if(!vis[nxt]) dfs(nxt, vis, adj, ans);
    }
    ans.push_back(cur);
}

signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        vector<int> vis(n+1, 0), ans, par(n+1);
        vector<vector<int>> adj(n+1);
        fox(i, n) {
            int p; cin >> p;
            par[i+1] = p;
            adj[p].pb(i+1);
        }
        dfs(0, vis, adj, ans); // toposort

        // find how many children each node has
        // reverse(all(ans));
        vector<int> pathlen(n+1, 0);
        for (int node : ans) {
            if (node == 0) continue;
            pathlen[par[node]] = max(pathlen[par[node]], pathlen[node]+1);
        }
        // fox(i, n+1) cout << pathlen[i] << ' '; cout << '\n'; 
        priority_queue<pii> pq; 
        for (int node : adj[0]) pq.push({pathlen[node], node});

        int cnt = 0;
        for (int sem=1; sem<=m && !pq.empty(); sem++) {
            queue<int> q; 
            for (int i = 0; i < k && !pq.empty(); i++) {
                int node = pq.top().S; pq.pop();
                cnt++;
                for (int nxt : adj[node]) q.push(nxt);
            }
            while (!q.empty()) {
                int nxt = q.front(); q.pop();
                pq.push({pathlen[nxt], nxt});
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}


/*
greedy on path length
*/