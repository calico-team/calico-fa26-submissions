#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class DSU {
  public:
    vector<int> parent;

    explicit DSU(int n = 0) { dsu_init(n); }

    void dsu_init(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int dsu_find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void dsu_union(int a, int b) {
        a = dsu_find(a), b = dsu_find(b);
        if (a != b) parent[a] = b;
    }
};

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> cell(n);
    for (int i = 0; i < n; i++) {
        cin >> cell[i];
    }
    DSU d(n * m);
    auto convert = [&](int i, int j) -> int { return i * m + j; };
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (cell[x][y] == cell[nx][ny] || cell[x][y] == '.' ||
                    cell[nx][ny] == '.') {
                    d.dsu_union(convert(x, y), convert(nx, ny));
                }
            }
        }
    }
    while (q--) {
        int x, y, tx, ty;
        cin >> x >> y >> tx >> ty;
        cout << (d.dsu_find(convert(x, y)) == d.dsu_find(convert(tx, ty))
                     ? "YES"
                     : "NO")
             << "\n";
    }
}

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
