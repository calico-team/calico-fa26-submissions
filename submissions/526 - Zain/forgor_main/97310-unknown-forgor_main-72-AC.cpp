#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    cin >> phase;

    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<vector<int>> adj(N + 1);
        vector<int> degree(N + 1, 0);

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            ++degree[u];
            ++degree[v];
        }

        priority_queue<int, vector<int>, greater<int>> leaves;
        for (int v = 1; v <= N; ++v)
            if (degree[v] == 1) leaves.push(v);

        vector<int> code;
        code.reserve(N - 2);
        int checksum = 0;

        for (int i = 0; i < N - 2; ++i) {
            int leaf = leaves.top();
            leaves.pop();

            int neighbor = -1;
            for (int v : adj[leaf]) {
                if (degree[v] > 0) {
                    neighbor = v;
                    break;
                }
            }

            code.push_back(neighbor);
            checksum ^= neighbor;
            degree[leaf] = 0;
            if (--degree[neighbor] == 1) leaves.push(neighbor);
        }

        for (int x : code) cout << x << ' ';
        cout << checksum << " 0\n";
    } else if (phase == "SECOND") {
        vector<int> a(N);
        for (int &x : a) cin >> x;

        int missing = -1;
        for (int i = 0; i < N - 2; ++i) {
            if (a[i] == -1) missing = i;
        }

        if (missing != -1) {
            int recovered = a[N - 2];
            for (int i = 0; i < N - 2; ++i)
                if (i != missing) recovered ^= a[i];
            a[missing] = recovered;
        }

        vector<int> degree(N + 1, 1);
        for (int i = 0; i < N - 2; ++i)
            ++degree[a[i]];

        priority_queue<int, vector<int>, greater<int>> leaves;
        for (int v = 1; v <= N; ++v)
            if (degree[v] == 1) leaves.push(v);

        for (int i = 0; i < N - 2; ++i) {
            int leaf = leaves.top();
            leaves.pop();
            int neighbor = a[i];

            cout << leaf << ' ' << neighbor << '\n';
            --degree[leaf];
            if (--degree[neighbor] == 1) leaves.push(neighbor);
        }

        int u = leaves.top(); leaves.pop();
        int v = leaves.top(); leaves.pop();
        cout << u << ' ' << v << '\n';
    }

    return 0;
}
