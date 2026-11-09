#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

struct DSU {
    vector<int> parent;

    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Earthquake> earthquakes(Q);

        for (int i = 0; i < Q; i++) {
            cin >> earthquakes[i].r
                >> earthquakes[i].c
                >> earthquakes[i].p;
        }

        vector<vector<long long>> ans(
            N, vector<long long>(M, 0)
        );

        DSU dsu(N * (M + 1));

        for (int i = Q - 1; i >= 0; i--) {
            int R = earthquakes[i].r;
            int C = earthquakes[i].c;
            int P = earthquakes[i].p;

            long long P2 = 1LL * P * P;

            for (int r = R - P; r <= R + P; r++) {

                long long dr = r - R;

                long long remaining = P2 - dr * dr;

                int dx = sqrt((long double)remaining);

                while (1LL * (dx + 1) * (dx + 1)
                       <= remaining) {
                    dx++;
                }

                while (1LL * dx * dx > remaining) {
                    dx--;
                }

                int L = max(0, C - dx);
                int H = min(M - 1, C + dx);

                int base = r * (M + 1);

                int pos = dsu.find(base + L);

                while (pos <= base + H) {

                    int c = pos - base;

                    long long dc = c - C;

                    long long shock =
                        P2 - dr * dr - dc * dc + 1;

                    ans[r][c] = shock;

                    dsu.parent[pos] = dsu.find(pos + 1);

                    pos = dsu.find(pos);
                }
            }
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                if (c > 0) cout << " ";
                cout << ans[r][c];
            }
            cout << '\n';
        }
    }

    return 0;
}
