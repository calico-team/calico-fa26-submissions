#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

pii dirs[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

struct DSU {
    vector<int> parents, counts;
    DSU(int n) : parents(n), counts(n, 1) {
        iota(parents.begin(), parents.end(), 0);
    }
    int find(int x) {
        return parents[x] == x ? x : (parents[x] = find(parents[x]));
    }
    // 0-indexed
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
    bool unite(int a, int b) {
        if (connected(a, b))
            return false;
        a = find(a);
        b = find(b);
        if (counts[b] > counts[a])
            swap(a, b);
        counts[a] += counts[b];
        parents[b] = parents[a];
        return true;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<string> grid(n);
    for (string& s : grid) cin >> s;

    DSU dsu(n * m);
    auto flatten = [m](int i, int j) {
        return i * m + j;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto [di, dj] : dirs) {
                int ni = i + di, nj = j + dj;
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (grid[i][j] != '.' && (grid[ni][nj] != grid[i][j] && grid[ni][nj] != '.')) continue;
                dsu.unite(flatten(i, j), flatten(ni, nj));
            }
        }
    }

    int i1, j1, i2, j2;
    while (q--) {
        cin >> i1 >> j1 >> i2 >> j2;
        if (dsu.connected(flatten(i1, j1), flatten(i2, j2))) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}