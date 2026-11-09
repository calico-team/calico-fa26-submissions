#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<vector<int>> child(N + 1);
        vector<int> parent(N + 1);
        vector<int> cnt(N + 1, 0);
        vector<int> sz(N + 1, 1);

        for (int i = 1; i <= N; i++) {
            cin >> parent[i];

            if (parent[i] != 0) {
                child[parent[i]].push_back(i);
                cnt[parent[i]]++;
            }
        }

        queue<int> q;

        for (int i = 1; i <= N; i++) {
            if (cnt[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int p = parent[u];

            if (p != 0) {
                sz[p] += sz[u];
                cnt[p]--;

                if (cnt[p] == 0)
                    q.push(p);
            }
        }

        priority_queue<pair<int, int>> pq;

        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0)
                pq.push({sz[i], i});
        }

        int ans = 0;

        for (int semester = 0; semester < M; semester++) {
            if (pq.empty()) break;

            vector<int> taken;

            for (int j = 0; j < K && !pq.empty(); j++) {
                int u = pq.top().second;
                pq.pop();

                taken.push_back(u);
                ans++;
            }

            for (int u : taken) {
                for (int v : child[u])
                    pq.push({sz[v], v});
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
