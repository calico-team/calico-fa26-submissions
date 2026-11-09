#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void solve() {
    int n, m, k; if (!(cin >> n >> m >> k)) return;
    
    vector<int> p(n + 1); vector<vector<int>> children(n + 1); vector<int> deg(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] != 0) {
            children[p[i]].push_back(i);
            deg[i]++;
        }
    }

    vector<int> in_deg = deg; queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_deg[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        if (p[u] != 0) {
            in_deg[p[u]]--;
            if (in_deg[p[u]] == 0) {
                q.push(p[u]);
            }
        }
    }
    
    vector<int> sz(n + 1, 1);
    vector<int> rev_topo = topo;
    reverse(rev_topo.begin(), rev_topo.end());
    for (int u : rev_topo) {
        for (int v : children[u]) {
            sz[u] += sz[v];
        }
    }

    auto cmp = [&](int a, int b) {
        if (sz[a] != sz[b]) {
            return sz[a] < sz[b];
        }
        return a > b;
    };
    
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            pq.push(i);
        }
    }
    
    int total_courses = 0;
    for (int sem = 0; sem < m; sem++) {
        if (pq.empty()) break;
        
        int taken_this_sem = 0;
        vector<int> newly_ready;
        
        while (!pq.empty() && taken_this_sem < k) {
            int u = pq.top(); pq.pop();
            taken_this_sem++; total_courses++;
            
            for (int v : children[u]) {
                deg[v]--;
                if (deg[v] == 0) {
                    newly_ready.push_back(v);
                }
            }
        }
        
        for (int v : newly_ready) {
            pq.push(v);
        }
    }
    cout << total_courses << "\n";
}

int main() {
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