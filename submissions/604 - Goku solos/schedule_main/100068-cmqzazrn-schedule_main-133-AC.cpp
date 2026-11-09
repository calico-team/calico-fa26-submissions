#include <bits/stdc++.h>
using namespace std;

vector<int> children[10005];
int height[10005];

int dfs(int u) {
    if (height[u] != 0) {
        return height[u];
    }

    height[u] = 1;

    for (int v : children[u]) {
        height[u] = max(height[u], 1 + dfs(v));
    }

    return height[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        for (int i = 0; i <= N; i++) {
            children[i].clear();
            height[i] = 0;
        }

        vector<int> roots;

        for (int i = 1; i <= N; i++) {
            int p;
            cin >> p;

            if (p == 0) {
                roots.push_back(i);
            } else {
                children[p].push_back(i);
            }
        }

        for (int i = 1; i <= N; i++) {
            dfs(i);
        }

        priority_queue<pair<int, int>> pq;

        for (int u : roots) {
            pq.push({height[u], u});
        }

        int answer = 0;

        for (int semester = 1;
             semester <= M && !pq.empty();
             semester++) {

            vector<int> nextSemester;

            int taken = 0;

            while (taken < K && !pq.empty()) {
                int u = pq.top().second;
                pq.pop();

                answer++;
                taken++;

                for (int v : children[u]) {
                    nextSemester.push_back(v);
                }
            }

            for (int v : nextSemester) {
                pq.push({height[v], v});
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
