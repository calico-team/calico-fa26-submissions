#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    vector<int> r(q), c(q), p(q);
    for (int i = 0; i < q; ++i) {
        cin >> r[i] >> c[i] >> p[i];
    }

    vector<vector<int>> a(n, vector<int>(m, 0));
    vector<vector<int>> nx(n, vector<int>(m + 2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            nx[i][j] = j;
        }
    }

    auto get_next = [&](auto& self, int i, int j) -> int {
        if (nx[i][j] == j) return j;
        return nx[i][j] = self(self, i, nx[i][j]);
    };

    for (int i = q - 1; i >= 0; --i) {
        int tr = r[i], tc = c[i], tp = p[i];
        int r1 = max(0, tr - tp);
        int r2 = min(n - 1, tr + tp);

        for (int x = r1; x <= r2; ++x) {
            long long dy = 1LL * tp * tp - 1LL * (x - tr) * (x - tr);
            if (dy < 0) continue;
            long long dx = sqrt(dy);
            while ((dx + 1) * (dx + 1) <= dy) dx++;
            while (dx * dx > dy) dx--;

            int c1 = max(0, tc - (int)dx);
            int c2 = min(m - 1, tc + (int)dx);

            int y = get_next(get_next, x, c1);
            while (y <= c2) {
                long long ds = 1LL * (x - tr) * (x - tr) + 1LL * (y - tc) * (y - tc);
                a[x][y] = tp * tp - ds + 1;
                nx[x][y] = get_next(get_next, x, y + 1);
                y = nx[x][y];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << a[i][j] << (j == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}