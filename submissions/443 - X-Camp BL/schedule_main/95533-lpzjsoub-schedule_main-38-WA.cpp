#include <bits/stdc++.h>
using namespace std;
void solve() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;
    vector<int> P(N + 1);
    vector<vector<int>> adj(N + 1);
    vector<int> ind(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> P[i];
        if (P[i] != 0) {
            adj[P[i]].push_back(i);
            ind[i]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (ind[i] == 0) q.push(i);
    }
    int totc = 0;
    for (int sem = 0; sem < M; ++sem) {
        if (q.empty()) break;
        int size = q.size();
        int take = min(size, K);
        totc += take;
        vector<int> cursem;
        for (int i = 0; i < take; ++i) {
            cursem.push_back(q.front());
            q.pop();
        }
        for (int i = take; i < size; ++i) {
            int u = q.front();
            q.pop();
            q.push(u);
        }
        for (int u : cursem) {
            for (int v : adj[u]) {
                ind[v]--;
                if (ind[v] == 0) {
                    q.push(v);
                }
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