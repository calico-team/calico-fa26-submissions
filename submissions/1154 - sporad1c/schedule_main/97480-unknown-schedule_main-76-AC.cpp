/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

void f() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;
    vector<int> p(n + 1);
    vector<vector<int>> g(n + 1);
    vector<int> r;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (p[i] == 0) {
            r.push_back(i);
        } else {
            g[p[i]].push_back(i);
        }
    }
    vector<int> d(n + 1, 0);
    auto f1 = [&](auto self, int u, int x) -> void {
        d[u] = x;
        for (int v : g[u]) {
            self(self, v, x + 1);
        }
    };
    for (int u : r) {
        f1(f1, u, 1);
    }
    vector<int> h(n + 1, 0);
    auto f2 = [&](auto self, int u) -> int {
        int x = 0;
        for (int v : g[u]) {
            if (d[v] <= m) {
                x = max(x, self(self, v));
            }
        }
        return h[u] = 1 + x;
    };
    for (int u : r) {
        if (d[u] <= m) {
            f2(f2, u);
        }
    }
    priority_queue<pair<int, int>> q;
    for (int u : r) {
        if (d[u] <= m) {
            q.push({h[u], u});
        }
    }
    int a = 0;
    for (int i = 1; i <= m; ++i) {
        if (q.empty()) break;
        int c = min((int)q.size(), k);
        vector<int> b;
        for (int j = 0; j < c; ++j) {
            auto [x, u] = q.top();
            q.pop();
            b.push_back(u);
        }
        a += c;
        for (int u : b) {
            for (int v : g[u]) {
                if (d[v] <= m) {
                    q.push({h[v], v});
                }
            }
        }
    }
    cout << a << "\n";
}
int main() {
    int t;
    if (cin >> t) {
        while (t--) f();
    }
    return 0;
}