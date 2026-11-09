
#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

int findNext(int x, vector<int>& parent) {
    int root = x;

    while (parent[root] != root)
        root = parent[root];

    while (parent[x] != x) {
        int nxt = parent[x];
        parent[x] = root;
        x = nxt;
    }

    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<Earthquake> events(q);

        int maxP = min((n - 1) / 2, (m - 1) / 2);

        for (auto& e : events) {
            cin >> e.r >> e.c >> e.p;
        }

        vector<vector<int>> radius(maxP + 1);

        for (int p = 0; p <= maxP; p++) {
            radius[p].resize(p + 1);

            for (int d = 0; d <= p; d++) {
                long long rem = 1LL * p * p - 1LL * d * d;
                int x = sqrt((long double)rem);

                while (1LL * (x + 1) * (x + 1) <= rem) x++;
                while (1LL * x * x > rem) x--;

                radius[p][d] = x;
            }
        }

        vector<long long> ans(n * m, 0);
        vector<int> parent(n * (m + 1));

        iota(parent.begin(), parent.end(), 0);

        for (int i = q - 1; i >= 0; i--) {
            int R = events[i].r;
            int C = events[i].c;
            int P = events[i].p;

            long long p2 = 1LL * P * P;

            for (int dr = -P; dr <= P; dr++) {
                int r = R + dr;
                int dc = radius[P][abs(dr)];

                int left = C - dc;
                int right = C + dc;

                int base = r * (m + 1);
                int col = findNext(base + left, parent) - base;

                while (col <= right) {
                    long long dx = col - C;

                    ans[r * m + col] = p2 - 1LL * dr * dr - dx * dx + 1;

                    int idx = base + col;
                    parent[idx] = findNext(idx + 1, parent);

                    col = parent[idx] - base;
                }
            }
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (c) cout << ' ';
                cout << ans[r * m + c];
            }
            cout << '\n';
        }
    }

    return 0;
}
