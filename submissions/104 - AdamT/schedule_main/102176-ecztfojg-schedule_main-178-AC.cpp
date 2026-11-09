#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "timer.h"
#else
struct Timer {
    Timer(string_view = "") {}
};
#endif

#ifdef DEBUG
#include "dbg.h"
#else
#define dbg(...) __VA_ARGS__
#endif

vector<vector<int>> adj;
vector<bool> visited;
vector<pair<int, int>> topo;

int dfs(int node) {
    visited[node] = true;
    int deps = 0;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            deps += 1 + dfs(neighbor);
        }
    }
    topo.emplace_back(node, deps);
    return deps;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    adj.assign(n + 5, vector<int>());
    visited.assign(n + 5, false);
    topo.clear();
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    dfs(0);
    reverse(topo.begin(), topo.end());
    dbg(topo);

    vector<int> deps(n + 5);
    for (auto& [node, count] : topo) {
        deps[node] = count;
    }
    dbg(deps);

    priority_queue<pair<int, int>> pq;
    for (auto& node : adj[0]) {
        pq.emplace(deps[node], node);
    }
    dbg(pq);

    int ans = 0;
    for (int sem = 0; sem < m; ++sem) {
        vector<int> next;
        for (int j = 0; j < k && !pq.empty(); ++j) {
            auto [count, node] = pq.top();
            pq.pop();
            ++ans;

            for (auto& neighbor : adj[node]) {
                next.push_back(neighbor);
            }
        }
        for (auto& node : next) {
            pq.emplace(deps[node], node);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    cout << flush;
    return 0;
}
