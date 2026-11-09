// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> a;
vector<int> p;

int MOD = 1000000;

void DFS(int u, int prev) {
    p[u] = prev;
    for (int v : a[u]) if (v != prev) {
        DFS(v, u);
    }
}

int main() {
	string s;
    cin >> s;
    if (s == "FIRST") {
        cin >> n;
        a.resize(n);
        p.resize(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            a[u - 1].push_back(v - 1);
            a[v - 1].push_back(u - 1);
        }
        DFS(0, -1);
        p[0] = 0;
        for (int i = 1; i < n; i++) p[0] = (p[0] + p[i]) % MOD;
        for (int i = 0; i < n; i++) cout << p[i] << " ";
        return 0;
    }
    int n;
    cin >> n;
    p.resize(n);
    for (int& x : p) cin >> x;
    if (p[0] != -1) {
        int sum = p[0];
        for (int i = 1; i < n; i++) {
            if (p[i] != -1) sum = (sum - p[i] + MOD) % MOD;
        }
        for (int i = 1; i < n; i++) {
            if (p[i] == -1) p[i] = sum;
        }
    }
    for (int i = 1; i < n; ++i) {
        cout << (p[i] + 1) << " " << (i + 1) << "\n";
    }
}
