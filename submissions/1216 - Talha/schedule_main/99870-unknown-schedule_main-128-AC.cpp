#include <bits/stdc++.h>
using namespace std;

int solve(int N, int M, int K, vector<int> &P) {
    vector<vector<int>> children(N + 1);
    for (int i = 1; i <= N; i++) {
        if (P[i - 1] != 0) children[P[i - 1]].push_back(i);
    }

    vector<int> height(N + 1, 1), sz(N + 1, 1);
    auto dfs = [&](auto& self, int u) -> void {
        for (int v : children[u]) {
            self(self, v);
            height[u] = max(height[u], height[v] + 1);
            sz[u] += sz[v];
        }
    };

    for (int i = 1; i <= N; i++) {
        if (P[i - 1] == 0) dfs(dfs, i);
    }

    auto comp = [&](int a, int b) {
        if (height[a] != height[b]) return height[a] < height[b];
        return sz[a] < sz[b];
    };
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);

    for (int i = 1; i <= N; i++) {
        if (P[i - 1] == 0) pq.push(i);
    }

    int taken = 0;
    for (int sem = 0; sem < M && !pq.empty(); sem++) {
        int can_take = min((int)pq.size(), K);
        vector<int> current_round;
        for (int i = 0; i < can_take; i++) {
            current_round.push_back(pq.top());
            pq.pop();
        }
        taken += can_take;
        for (int u : current_round) {
            for (int v : children[u]) pq.push(v);
        }
    }
    return taken;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P) << '\n';
    }
}