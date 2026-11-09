#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<int> indeg(n+1);
    vector<vector<int>> adj(n+1);
    for(int i=1;i<=n;i++) {
        int p; cin >> p;

        if(p==0) continue;
        adj[p].push_back(i);
        indeg[i] ++;
    }

    vector<int> deepth(n+1, -1);
    auto f = [&](auto && f, int cur) -> void {
        int mx = 0;
        for(auto &next:adj[cur]) {
            if(deepth[next] == -1) f(f, next);
            mx = max(mx, deepth[next]);
        }
        deepth[cur] = mx + 1;
    };

    for(int i=1;i<=n;i++) 
        if(indeg[i] == 0) 
            f(f, i);
    
    priority_queue<pair<int, int>> pq;
    for(int i=1;i<=n;i++) 
        if(indeg[i] == 0)
            pq.push({deepth[i], i});
    
    int ans = 0;
    for(int i=1;i<=m;i++) {
        if(pq.empty()) break;
        
        int c = k;
        queue<int> q;
        while(c>0 && !pq.empty()) {
            auto [d, cur] = pq.top();
            ans ++, c--; pq.pop();

            for(auto &next:adj[cur]) {
                indeg[next] --;
                if(indeg[next] == 0) q.push(next);
            }
        }

        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            pq.push({deepth[cur], cur});
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 1; cin >> t;
    while(t--) solve();
}