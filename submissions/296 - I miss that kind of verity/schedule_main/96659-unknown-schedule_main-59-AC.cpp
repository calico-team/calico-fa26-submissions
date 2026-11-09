#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pull = pair<ull, ull>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> p(n);

        vector<vector<int>> children(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            --p[i];

            if (p[i] != -1) {
                children[p[i]].push_back(i);
            }
        }

        vector<int> height(n, 1);
        function<void(int)> dfs = [&](int u) {
            for (int v : children[u]) {
                dfs(v);
                height[u] = max(height[u], height[v] + 1);
            }
        };

        auto cmp = [&](int a, int b) {
            return height[a] < height[b];
        };

        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < n; i++) {
            if (p[i] == -1) {
                dfs(i);
                pq.push(i);
            }
        }

        int ans = 0;
        for (int round = 0; round < m; round++) {
            vector<int> next;
            int ct = 0;

            while (!pq.empty() && ct < k) {
                int u = pq.top();
                pq.pop();
                ct++;
                for (int v : children[u]) {
                    next.push_back(v);
                }
            }

            ans += ct;
            for (int v : next) {
                pq.push(v);
            }
        }

        cout << ans << '\n';
    }

}