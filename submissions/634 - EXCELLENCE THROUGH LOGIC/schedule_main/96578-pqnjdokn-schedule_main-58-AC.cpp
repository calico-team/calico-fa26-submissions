
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
    vector<int> order;
    vector<int> st;

    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) st.push_back(i);
    }

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        order.push_back(u);

        for (int v : child[u]) {
            st.push_back(v);
        }
    }

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];

        for (int v : child[u]) {
            height[u] = max(height[u], height[v] + 1);
        }
    }

    priority_queue<pair<int, int>> pq;

    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            pq.push({height[i], i});
        }
    }

    int ans = 0;

    for (int semester = 1; semester <= m; semester++) {
        vector<int> selected;

        for (int j = 0; j < k && !pq.empty(); j++) {
            int u = pq.top().second;
            pq.pop();

            selected.push_back(u);
            ans++;
        }

        for (int u : selected) {
            for (int v : child[u]) {
                pq.push({height[v], v});
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
