#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Function to compute subtree sizes using DFS
int dfs_size(int u, const vector<vector<int>>& adj, vector<int>& sz) {
    int s = 1;
    for (int v : adj[u]) {
        s += dfs_size(v, adj, sz);
    }
    sz[u] = s;
    return s;
}

void solve() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;

    vector<int> p(n + 1);
    vector<vector<int>> adj(n + 1);
    vector<int> roots;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (p[i] == 0) {
            roots.push_back(i);
        } else {
            adj[p[i]].push_back(i);
        }
    }

    vector<int> sz(n + 1, 0);
    for (int root : roots) {
        dfs_size(root, adj, sz);
    }

    // Max-heap storing pairs of (subtree_size, node_id)
    priority_queue<pair<int, int>> pq;

    // Push all root courses (no prerequisites) into the priority queue
    for (int root : roots) {
        pq.push({sz[root], root});
    }

    int total_courses_taken = 0;

    // Simulate each semester
    for (int sem = 0; sem < m; ++sem) {
        if (pq.empty()) {
            break;
        }

        int courses_this_sem = 0;
        vector<int> taken_nodes;

        // Take up to K courses in the current semester
        while (!pq.empty() && courses_this_sem < k) {
            auto [s, u] = pq.top();
            pq.pop();
            taken_nodes.push_back(u);
            courses_this_sem++;
        }

        total_courses_taken += courses_this_sem;

        // Push children of the taken courses into the queue for future semesters
        for (int u : taken_nodes) {
            for (int v : adj[u]) {
                pq.push({sz[v], v});
            }
        }
    }

    cout << total_courses_taken << "\n";
}

int main() {
    // Optimize standard input/output operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
