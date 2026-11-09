#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string phase;
    int n;
    cin >> phase >> n;
    vector<int> code(n + 1);
    if (phase == "FIRST") {
        vector<vector<int>> neighbors(n + 1);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }
        vector<int> order{1};
        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (int v : neighbors[u]) {
                if (v == code[u]) continue;
                code[v] = u;
                order.push_back(v);
            }
        }
        for (int v = 2; v <= n; ++v) code[1] ^= code[v];
        for (int v = 1; v <= n; ++v) cout << code[v] << (v == n ? '\n' : ' ');
    } else {
        int missing = 0, checksum = 0;
        for (int v = 1; v <= n; ++v) {
            cin >> code[v];
            if (code[v] == -1) missing = v;
            else checksum ^= code[v];
        }
        code[missing] = checksum;
        for (int v = 2; v <= n; ++v) cout << code[v] << ' ' << v << '\n';
    }
}
