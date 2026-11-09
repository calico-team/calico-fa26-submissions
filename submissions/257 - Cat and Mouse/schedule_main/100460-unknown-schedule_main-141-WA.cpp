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
        dfs(1, vis, adj, ans); // toposort

        // find how many children each node has
        vector<int> pathlen(n+1, 0);
        for (int node : ans) {
            if (pathlen[node]) continue;
            int cur = node, len = 0;
            while (par[cur]) {
                cur = par[cur];
                len++;
                pathlen[cur] = len;
            }
        }
        // fox(i, n+1) cout << pathlen[i] << ' '; cout << '\n';
        priority_queue<pii> pq; 
        for (int node : adj[0]) pq.push({pathlen[node], node});

        int cnt = 0, sem = 1, semcnt = 0;
        queue<int> q; 
        while (sem <= m) {
            if (!pq.empty()) {
                int nxt = pq.top().S; 
                // cout << ""<< sem << ", " << semcnt << ", " << nxt << '\n';
                for (int child : adj[nxt]) q.push(child);
                pq.pop();
                cnt++;
            }
            semcnt++;
            if (semcnt == k) {
                semcnt = 0; sem++;
                while (!q.empty()) {
                    pq.push({pathlen[q.front()], q.front()}); q.pop();
                }
            }
        }
        cout << cnt << '\n';        
    }

    return 0;
}


/*
z coord useless
only care about insersection where (x, y, t) is all equal
horizontal drones only ever intersect with vertical drones
let drone 1 be H, drone 2 be V: intersect at (x_2, y_1)
-> intersect iff (0 < x_2-x_1 == y_1-y_2 < K) 

sort bsearch

not possible to have >2 drones intersect at once

collect first, move second
*/