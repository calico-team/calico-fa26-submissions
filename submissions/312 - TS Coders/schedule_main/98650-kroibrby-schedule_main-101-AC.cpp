#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m, k; cin >> n >> m >> k;
        vector<int> p(n), height(n, 1), childCount(n, 0);
        vector<vector<int>> children(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            if (p[i]) children[p[i] - 1].push_back(i);
        }
        vector<int> order;
        order.reserve(n);
        queue<int> q;
        for (int i = 0; i < n; ++i) if (p[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int v : children[u]) q.push(v);
        }
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            for (int v : children[u]) height[u] = max(height[u], height[v] + 1);
        }
        priority_queue<pair<int,int>> available;
        for (int i = 0; i < n; ++i) if (p[i] == 0) available.push({height[i], i});
        int done = 0;
        for (int sem = 0; sem < m && !available.empty(); ++sem) {
            vector<int> take;
            for (int j = 0; j < k && !available.empty(); ++j) {
                take.push_back(available.top().second);
                available.pop();
            }
            done += (int)take.size();
            for (int u : take) for (int v : children[u]) available.push({height[v], v});
        }
        cout << done << '\n';
    }
}
