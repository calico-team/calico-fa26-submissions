#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        int n, m, k; cin >> n >> m >> k;
        int p[n + 1];
        vector <int> adj[n + 1];
        priority_queue <pair <int, int>> pq;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i]) adj[p[i]].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            if (!p[i]) pq.push({(int)adj[i].size(), i});
        }
        int ans = 0;
        while (m--) {
            vector <int> nwpos;
            for (int i = 0; i < k && !pq.empty(); i++) {
                int x = pq.top().second;
                pq.pop();
                ans++;
                for (auto j : adj[x]) {
                    nwpos.push_back(j);
                }
            }
            for (auto j : nwpos) pq.push({(int)adj[j].size(), j});
        }
        cout << ans << '\n';
    }
}