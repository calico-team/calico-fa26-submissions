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
        vector<int> P(N + 1);
        vector<vector<int>> children(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> P[i];
            if (P[i] != 0) children[P[i]].push_back(i);
        }

        // height = longest chain from node down to a leaf (in nodes)
        vector<int> height(N + 1, 1);
        vector<int> order;
        order.reserve(N);
        vector<int> stack;
        for (int i = 1; i <= N; ++i) if (P[i] == 0) stack.push_back(i);
        while (!stack.empty()) {
            int u = stack.back(); stack.pop_back();
            order.push_back(u);
            for (int v : children[u]) stack.push_back(v);
        }
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            int best = 0;
            for (int v : children[u]) best = max(best, height[v]);
            height[u] = best + 1;
        }

        // Hu's algorithm: each semester take up to K available nodes
        // with largest height (most critical).
        // For an out-tree (one prerequisite per job) this is optimal
        // for makespan, and its prefix of length M maximises throughput.
        using Node = pair<int,int>; // (height, id)
        priority_queue<Node> pq;
        for (int i = 1; i <= N; ++i) if (P[i] == 0) pq.emplace(height[i], i);

        long long taken = 0;
        vector<int> cur;
        cur.reserve(K);
        for (long long sem = 0; sem < M && !pq.empty(); ++sem) {
            cur.clear();
            for (int j = 0; j < K && !pq.empty(); ++j) {
                auto [h, u] = pq.top(); pq.pop();
                cur.push_back(u);
                ++taken;
            }
            for (int u : cur) {
                for (int v : children[u]) pq.emplace(height[v], v);
            }
        }
        cout << taken << "\n";
    }
    return 0;
}