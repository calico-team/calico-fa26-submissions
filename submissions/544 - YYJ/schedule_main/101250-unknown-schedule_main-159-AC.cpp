#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;
vector<int> p, h;
vector<vector<int>> adj;

void dfs(int u) {
    h[u] = 1;
    for (int &v : adj[u]) { dfs(v); h[u] = max(h[u], h[v] + 1); }
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        p.clear(); p.resize(n + 1); h.clear(); h.resize(n + 1); adj.clear(); adj.resize(n + 1);
        for (int i = 1; i <= n; i++) { cin >> p[i]; adj[p[i]].push_back(i); }
        
        dfs(0);
        
        priority_queue<pair<int,int>> pq;
        for (int &v : adj[0]) pq.push({h[v], v}); // classes you can take
        
        int ans = 0;
        for (int sem = 0; sem < m; sem++) {
            vector<int> take;
            while (!pq.empty() && take.size() < k) { take.push_back(pq.top().second); pq.pop(); }
            for (int &u : take) for (int &v : adj[u]) pq.push({h[v], v});
            ans += (int) take.size();
        }
        cout << ans << "\n";
    }
}
