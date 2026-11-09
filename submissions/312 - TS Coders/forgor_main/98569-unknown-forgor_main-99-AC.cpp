#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string phase;
    if (!(cin >> phase)) return 0;
    int n; cin >> n;
    if (phase == "FIRST") {
        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v); g[v].push_back(u);
        }
        vector<int> degree(n + 1);
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 1; i <= n; ++i) {
            degree[i] = (int)g[i].size();
            if (degree[i] == 1) q.push(i);
        }
        vector<int> prufer;
        prufer.reserve(max(0, n - 2));
        for (int k = 0; k < n - 2; ++k) {
            int leaf = q.top(); q.pop();
            int p = 0;
            for (int v : g[leaf]) if (degree[v] > 0) { p = v; break; }
            prufer.push_back(p);
            degree[leaf] = 0;
            if (--degree[p] == 1) q.push(p);
        }
        int parity = 0;
        for (int x : prufer) parity ^= x;
        for (int x : prufer) cout << x << ' ';
        cout << parity << ' ' << 0 << '\n';
    } else {
        vector<int> a(n);
        int missing = -1;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] == -1) missing = i;
        }
        vector<int> prufer;
        prufer.reserve(max(0, n - 2));
        if (missing >= 0 && missing < n - 2) {
            int check = a[n - 2];
            prufer = vector<int>(a.begin(), a.begin() + (n - 2));
            int other = 0;
            for (int i = 0; i < n - 2; ++i) if (i != missing) other ^= prufer[i];
            prufer[missing] = check ^ other;
        } else {
            for (int i = 0; i < n - 2; ++i) prufer.push_back(a[i]);
        }
        vector<int> degree(n + 1, 1);
        for (int x : prufer) ++degree[x];
        priority_queue<int, vector<int>, greater<int>> leaves;
        for (int i = 1; i <= n; ++i) if (degree[i] == 1) leaves.push(i);
        for (int x : prufer) {
            int leaf = leaves.top(); leaves.pop();
            cout << leaf << ' ' << x << '\n';
            if (--degree[x] == 1) leaves.push(x);
            degree[leaf] = 0;
        }
        int u = leaves.top(); leaves.pop();
        int v = leaves.top();
        cout << u << ' ' << v << '\n';
    }
}
