#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t; cin >> t;
    while (t--) {
        int n, m,k;
        cin >> n >>m >> k;
        
        vector<int> p(n + 1), deg(n + 1), h(n + 1);
        vector<vector<int>> adj(n + 1);
        
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i]) {
                adj[p[i]].push_back(i);
                deg[p[i]]++;
            }
        }
        vector<int> q(n +1);
        int l = 0, r =0;
        for (int i =1; i<= n; i++) if (!deg[i]) q[r++] = i;
        
        while (l < r) {
            int u =q[l++];
            if (!p[u]) continue;
            int v = p[u];
            h[v] = max(h[v],h[u] + 1);
            if (--deg[v] ==0) q[r++] = v;
        }

        priority_queue<pair<int,int>> pq;
        for (int i = 1; i <= n; i++) if (!p[i]) pq.push({h[i], i});

        int ans = 0;
        for (int s = 0; s <m && ans <n && !pq.empty(); s++) {
            vector<int> cur;
            for (int j =0; j <k && !pq.empty(); j++) {
                int u =pq.top().second; pq.pop();
                cur.push_back(u);
                ans++;
            }
            for (int u : cur) {
                for (int v :adj[u]) pq.push({h[v], v});
            }
        }
        cout << ans << '\n';
    }
    
    return 0;
}