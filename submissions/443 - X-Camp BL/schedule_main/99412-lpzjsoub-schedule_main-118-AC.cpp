#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int tol(int u, const vector<vector<int>>& adj, vector<int>& hgt) {
    if (hgt[u] != -1) return hgt[u];
    int h = 1;
    for (int v : adj[u]) {
        h = max(h, 1 + tol(v, adj, hgt));
    }
    return hgt[u] = h;
}
void solve() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;
    vector<vector<int>> adj(N + 1);
    vector<int> P(N + 1);
    vector<int> roots;
    for (int i = 1; i <= N; ++i) {
        cin >> P[i];
        if (P[i] == 0) {
            roots.push_back(i);
        } else {
            adj[P[i]].push_back(i);
        }
    }
    vector<int> hgt(N + 1, -1);
    for (int r : roots) {
        tol(r, adj, hgt);
    }
    priority_queue<pair<int, int>> pq;
    for (int r : roots) {
        pq.push({hgt[r], r});
    }
    int totc = 0;
    for (int sem = 0; sem < M; ++sem) {
        if (pq.empty()) break;
        int take_count = min(K, (int)pq.size());
        vector<int> curs;
        for (int i = 0; i < take_count; ++i) {
            auto [h, u] = pq.top();
            pq.pop();
            curs.push_back(u);
            totc++;
        }
        for (int u : curs) {
            for (int v : adj[u]) {
                pq.push({hgt[v], v});
            }
        }
    }
    cout << totc << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}