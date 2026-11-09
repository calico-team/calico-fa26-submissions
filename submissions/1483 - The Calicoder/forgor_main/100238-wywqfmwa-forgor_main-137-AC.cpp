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

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(N + 1, -1);
        queue<int> q;

        parent[1] = 0;
        q.push(1);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        int checksum = 0;

        for (int i = 2; i <= N; i++) {
            checksum ^= parent[i];
        }

        cout << checksum;

        for (int i = 2; i <= N; i++) {
            cout << " " << parent[i];
        }

        cout << '\n';
    }

    else if (phase == "SECOND") {
        vector<int> A(N + 1);

        int missing = -1;

        for (int i = 1; i <= N; i++) {
            cin >> A[i];

            if (A[i] == -1) {
                missing = i;
            }
        }

        if (missing != 1) {
            int value = A[1];

            for (int i = 2; i <= N; i++) {
                if (i != missing) {
                    value ^= A[i];
                }
            }

            A[missing] = value;
        }


        for (int i = 2; i <= N; i++) {
            cout << i << " " << A[i] << '\n';
        }
    }

    return 0;
}