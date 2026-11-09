#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    int n;
    cin >> phase >> n;

    if (phase == "FIRST") {
        vector<vector<int>> adj(n + 1);
        vector<int> degree(n + 1, 0);

        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        priority_queue<int, vector<int>, greater<int>> leaves_pq;

        for (int i = 1; i <= n; ++i) {
            if (degree[i] == 1) {
                leaves_pq.push(i);
            }
        }

        vector<int> code_output(n, 0);
        int checksum = 0;

        for (int i = 0; i < n - 2; ++i) {
            int u = leaves_pq.top();
            leaves_pq.pop();
            degree[u] = 0;

            int parent = 0;
            for (int x : adj[u]) {
                if (degree[x] > 0) {
                    parent = x;
                    break;
                }
            }

            code_output[i] = parent;
            checksum ^= parent;

            degree[parent]--;
            if (degree[parent] == 1) {
                leaves_pq.push(parent);
            }
        }

        code_output[n - 2] = checksum;

        for (int i = 0; i < n; ++i) {
            cout << code_output[i] << (i + 1 == n ? '\n' : ' ');
        }

    } else if (phase == "SECOND") {
        vector<int> code_input(n);
        int missing_index = -1;

        for (int i = 0; i < n; ++i) {
            cin >> code_input[i];
            if (code_input[i] == -1) {
                missing_index = i;
            }
        }

        if (missing_index < n - 2) {
            int recovered_value = code_input[n - 2];

            for (int i = 0; i < n - 2; ++i) {
                if (i != missing_index) {
                    recovered_value ^= code_input[i];
                }
            }

            code_input[missing_index] = recovered_value;
        }

        vector<int> degree(n + 1, 1);

        for (int i = 0; i < n - 2; ++i) {
            degree[code_input[i]]++;
        }

        priority_queue<int, vector<int>, greater<int>> leaves_pq;

        for (int i = 1; i <= n; ++i) {
            if (degree[i] == 1) {
                leaves_pq.push(i);
            }
        }

        for (int i = 0; i < n - 2; ++i) {
            int u = leaves_pq.top();
            leaves_pq.pop();

            int v = code_input[i];
            cout << u << ' ' << v << '\n';

            degree[u]--;
            degree[v]--;
            if (degree[v] == 1) {
                leaves_pq.push(v);
            }
        }

        int u = leaves_pq.top();
        leaves_pq.pop();

        cout << u << ' ' << leaves_pq.top() << '\n';
    }

    return 0;
}
