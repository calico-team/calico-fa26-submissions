#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<int> par(N + 1, 0);
        vector<vector<int>> child(N + 1);

        for (int i = 1; i <= N; ++i) {
            cin >> par[i];
            if (par[i] != 0) {
                child[par[i]].push_back(i);
            }
        }

        // 从所有根出发 BFS 求 depth
        vector<int> depth(N + 1, -1);
        queue<int> q;

        for (int i = 1; i <= N; ++i) {
            if (par[i] == 0) {
                depth[i] = 0;
                q.push(i);
            }
        }

        int maxDepth = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            maxDepth = max(maxDepth, depth[u]);

            for (int v : child[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }

        // depth 直方图
        vector<long long> cnt(maxDepth + 1, 0);
        for (int i = 1; i <= N; ++i) {
            ++cnt[depth[i]];
        }

        long long answer = N;
        long long shallower = 0;                  // cnt_{depth < d}
        int limit = (int)min<long long>(M, (long long)maxDepth + 1);

        for (int d = 0; d <= limit; ++d) {
            if (d > 0) {
                shallower += cnt[d - 1];
            }
            long long taken = shallower + (long long)(M - d) * K;
            answer = min(answer, taken);
        }

        cout << answer << '\n';
    }

    return 0;
}
