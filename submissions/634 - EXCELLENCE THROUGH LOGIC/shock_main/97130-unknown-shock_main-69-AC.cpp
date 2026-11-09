
#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

int findNext(vector<vector<int>>& parent, int r, int x) {
    int y = x;

    while (parent[r][y] != y) {
        y = parent[r][y];
    }

    while (parent[r][x] != x) {
        int next = parent[r][x];
        parent[r][x] = y;
        x = next;
    }

    return y;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<Earthquake> events(q);

    for (int i = 0; i < q; i++) {
        cin >> events[i].r >> events[i].c >> events[i].p;
    }

    vector<vector<int>> ans(n, vector<int>(m, 0));

    vector<vector<int>> parent(n, vector<int>(m + 1));

    for (int r = 0; r < n; r++) {
        iota(parent[r].begin(), parent[r].end(), 0);
    }

    for (int i = q - 1; i >= 0; i--) {
        int R = events[i].r;
        int C = events[i].c;
        int P = events[i].p;

        int p2 = P * P;

        for (int r = R - P; r <= R + P; r++) {
            int dy = r - R;
            int remaining = p2 - dy * dy;

            int dx = (int)sqrt(remaining);

            while ((dx + 1) * (dx + 1) <= remaining)
                dx++;

            while (dx * dx > remaining)
                dx--;

            int L = C - dx;
            int H = C + dx;

            int c = findNext(parent, r, L);

            while (c <= H) {
                int dist2 = dy * dy + (c - C) * (c - C);

                ans[r][c] = p2 - dist2 + 1;

                parent[r][c] = findNext(parent, r, c + 1);

                c = parent[r][c];
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (c) cout << ' ';
            cout << ans[r][c];
        }
        cout << '\n';
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
