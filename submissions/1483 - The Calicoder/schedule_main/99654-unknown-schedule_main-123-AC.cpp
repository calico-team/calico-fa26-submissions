#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<vector<int>> children(N + 1);
        vector<int> parent(N + 1);

        for (int i = 1; i <= N; i++) {
            cin >> parent[i];

            if (parent[i] != 0) {
                children[parent[i]].push_back(i);
            }
        }

        vector<int> height(N + 1, 1);

        queue<int> q;
        vector<int> order;

        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            order.push_back(u);

            for (int v : children[u]) {
                q.push(v);
            }
        }

        reverse(order.begin(), order.end());

        for (int u : order) {
            for (int v : children[u]) {
                height[u] = max(height[u], height[v] + 1);
            }
        }

        priority_queue<pair<int, int>> pq;

        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) {
                pq.push({height[i], i});
            }
        }

        int total = 0;

        for (int semester = 0; semester < M; semester++) {
            vector<int> taken;

            for (int j = 0; j < K && !pq.empty(); j++) {
                int u = pq.top().second;
                pq.pop();

                taken.push_back(u);
                total++;
            }

            for (int u : taken) {
                for (int v : children[u]) {
                    pq.push({height[v], v});
                }
            }

            if (pq.empty()) {
                break;
            }
        }

        cout << total << '\n';
    }
}