
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    cin >> phase;

    int n;
    cin >> n;

    if (phase == "FIRST") {
        vector<vector<int>> adj(n + 1);

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n + 1, 0);
        vector<int> st = {1};

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                st.push_back(v);
            }
        }

        int checksum = 0;

        for (int i = 2; i <= n; i++) {
            checksum ^= parent[i];
        }

        cout << checksum;

        for (int i = 2; i <= n; i++) {
            cout << " " << parent[i];
        }

        cout << '\n';
    }
    else {
        vector<int> a(n + 1);
        int missing = -1;

        for (int i = 1; i <= n; i++) {
            cin >> a[i];

            if (a[i] == -1) {
                missing = i;
            }
        }

        if (missing != 1) {
            int recovered = a[1];

            for (int i = 2; i <= n; i++) {
                if (i != missing) {
                    recovered ^= a[i];
                }
            }

            a[missing] = recovered;
        }

        for (int i = 2; i <= n; i++) {
            cout << i << " " << a[i] << '\n';
        }
    }

    return 0;
}
