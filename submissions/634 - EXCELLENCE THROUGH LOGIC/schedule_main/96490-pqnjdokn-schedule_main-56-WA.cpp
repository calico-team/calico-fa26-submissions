
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> p(n + 1);
    vector<vector<int>> child(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];

        if (p[i] != 0) {
            child[p[i]].push_back(i);
        }
    }

    vector<int> height(n + 1, 1);

    for (int i = n; i >= 1; i--) {
        for (int v : child[i]) {
            height[i] = max(height[i], height[v] + 1);
        }
    }

    priority_queue<pair<int, int>> pq;

    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            pq.push({height[i], i});
        }
    }

    int answer = 0;

    for (int semester = 1; semester <= m; semester++) {
        vector<int> selected;

        for (int j = 0; j < k && !pq.empty(); j++) {
            int u = pq.top().second;
            pq.pop();

            selected.push_back(u);
            answer++;
        }

        for (int u : selected) {
            for (int v : child[u]) {
                pq.push({height[v], v});
            }
        }

        if (pq.empty()) break;
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
