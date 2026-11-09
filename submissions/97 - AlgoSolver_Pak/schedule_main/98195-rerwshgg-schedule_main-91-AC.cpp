#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        long long M;
        int K;
        cin >> N >> M >> K;

        vector<int> P(N + 1, 0);
        for (int i = 1; i <= N; i++) cin >> P[i];

        vector<vector<int>> child(N + 1);
        vector<int> indeg(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            if (P[i] != 0) {
                child[P[i]].push_back(i);
                indeg[i] = 1;
            }
        }

        // Kahn - topological order
        queue<int> q;
        for (int i = 1; i <= N; i++) if (indeg[i] == 0) q.push(i);
        vector<int> order;
        vector<int> ok(N + 1, 0);
        vector<int> indeg2 = indeg;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ok[u] = 1;
            order.push_back(u);
            for (int v : child[u]) {
                indeg2[v]--;
                if (indeg2[v] == 0) q.push(v);
            }
        }

        // height = is course ke neeche sab se lambi chain
        vector<int> height(N + 1, 0);
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            int best = 0;
            for (int v : child[u]) if (ok[v]) best = max(best, height[v]);
            height[u] = best + 1;
        }

        // shuru me sirf P = 0 wale available
        priority_queue<pair<int,int>> pq;
        for (int i = 1; i <= N; i++) if (ok[i] && P[i] == 0) pq.push({height[i], i});

        long long ans = 0;
        for (long long sem = 0; sem < M; sem++) {
            if (pq.empty()) break;
            vector<int> taken;
            for (int c = 0; c < K && !pq.empty(); c++) {
                int u = pq.top().second; pq.pop();
                taken.push_back(u);
                ans++;
            }
            for (int u : taken) {
                for (int v : child[u]) if (ok[v]) pq.push({height[v], v});
            }
        }
        cout << ans << '\n';
    }
    return 0;
}