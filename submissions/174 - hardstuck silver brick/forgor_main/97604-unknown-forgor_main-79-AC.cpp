#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string phase; int n; cin >> phase >> n;
    if (phase == "FIRST") {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> arr(n + 1, 0);
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) if (!vis[v]) {
                vis[v] = true;
                arr[v] = u;
                q.push(v);
            }
        }

        int res = 0;
        for (int i = 2; i <= n; i++) res ^= arr[i];
        cout << res;
        for (int i = 2; i <= n; i++) cout << " " << arr[i];
        cout << endl;
    } else {
        vector<ll> arr(n + 1);
        int ind = 0;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            if (arr[i] == -1) ind = i;
        }
        if (ind != 1) {
            ll res = arr[1];
            for (int i = 2; i <= n; i++) if (i != ind) res ^= arr[i];
            arr[ind] = res;
        }
        for (int i = 2; i <= n; i++) cout << i << " " << arr[i] << endl;
    }
}