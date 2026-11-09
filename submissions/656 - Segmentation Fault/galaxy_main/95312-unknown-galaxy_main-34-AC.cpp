#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> g(n);
    DSU dsu(n*m);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i*m+j;
            if (i + 1 < n) {
                char a = g[i][j];
                char b = g[i + 1][j];
                if (a==b || a=='.' || b=='.') {
                    dsu.unite(u, (i+1)*m + j);
                }
            }

            if (j + 1 < m) {
                char a = g[i][j];
                char b = g[i][j + 1];
                if (a ==b || a=='.' || b=='.') {
                    dsu.unite(u, i*m +j+1);
                }
            }
        }
    }

    while (q--) {
        int alpha, beta, gamma, sigma;
        cin >> alpha >> beta >> gamma >> sigma;
        if (dsu.find(alpha*m+ beta)==dsu.find(gamma*m+sigma)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return;
} /*
DSU
verity falsity mog
cell == node
connect if {
    one or both is == '.'
    or
    same colour
}
ignore mode?
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}