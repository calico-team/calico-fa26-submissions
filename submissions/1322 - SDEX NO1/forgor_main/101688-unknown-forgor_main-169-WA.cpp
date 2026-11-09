
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    string phase;
    cin >> phase;
    if (phase == "FIRST") {
        int N;
        cin >> N;
        vector<vector<int> > adj(N + 1);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> A(N + 1);
        vector<int> parent(N + 1, 0);
        vector<bool> vis(N + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        int root_child = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j];
                if (!vis[v]) {
                    vis[v] = true;
                    parent[v] = u;
                    if (u == 1 && root_child == -1) {
                        root_child = v;
                    }
                    q.push(v);
                }
            }
        }
        A[1] = root_child;
        for (int i = 2; i <= N; ++i) {
            A[i] = parent[i];
        }
        for (int i = 1; i <= N; ++i) {
            if (i > 1) cout << " ";
            cout << A[i];
        }
        cout << "\n";
    } else {
        int N;
        cin >> N;
        vector<int> A(N + 1);
        int bad_idx = -1;
        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
            if (A[i] == -1) {
                bad_idx = i;
            }
        }
        vector<int> cnt(N + 1, 0);
        vector<pair<int, int> > edges;
        for (int i = 1; i <= N; ++i) {
            if (A[i] == -1) continue;
            int u = i, v = A[i];
            edges.push_back(make_pair(u, v));
            cnt[u]++;
            cnt[v]++;
        }
        int a = -1, b = -1;
        for (int i = 1; i <= N; ++i) {
            if (cnt[i] % 2 == 1) {
                if (a == -1) a = i;
                else b = i;
            }
        }
        edges.push_back(make_pair(a, b));
        for (int i = 0; i < edges.size(); i++) {
            cout << edges[i].first << " " << edges[i].second << "\n";
        }
    }
    return 0;
}

