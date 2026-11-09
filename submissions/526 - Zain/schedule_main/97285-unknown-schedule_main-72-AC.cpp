
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

        vector<int> parent(N + 1);
        vector<int> remaining(N + 1, 0);
        vector<int> height(N + 1, 1);
        vector<vector<int>> children(N + 1);

        for (int i = 1; i <= N; i++) {
            cin >> parent[i];

            if (parent[i] != 0) {
                children[parent[i]].push_back(i);
                remaining[parent[i]]++;
            }
        }

        // Calculate longest remaining prerequisite chains
        queue<int> q;

        for (int i = 1; i <= N; i++) {
            if (remaining[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int p = parent[u];

            if (p != 0) {
                height[p] = max(height[p], height[u] + 1);

                remaining[p]--;

                if (remaining[p] == 0)
                    q.push(p);
            }
        }

        // Available courses, highest height first
        priority_queue<pair<int, int>> ready;

        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0)
                ready.push({height[i], i});
        }

        int answer = 0;

        for (int sem = 0; sem < M && !ready.empty(); sem++) {
            vector<int> taken;

            // Take up to K available courses
            for (int j = 0; j < K && !ready.empty(); j++) {
                int u = ready.top().second;
                ready.pop();

                taken.push_back(u);
                answer++;
            }

            // Unlock courses for the NEXT semester
            for (int u : taken) {
                for (int v : children[u]) {
                    ready.push({height[v], v});
                }
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
