#include <bits/stdc++.h>
using namespace std;

inline int find_par(vector<int> &par, int x) {
    int root = x;
    while (par[root] != root) root = par[root];
    while (par[x] != x) {
        int nxt = par[x];
        par[x] = root;
        x = nxt;
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 0; tc < T; ++tc) {
        int N, M, Q;
        cin >> N >> M >> Q;
        struct Quake { int r, c, p; };
        vector<Quake> qs(Q);
        for (int i = 0; i < Q; ++i) cin >> qs[i].r >> qs[i].c >> qs[i].p;

        vector<long long> ans((size_t)N * M, 0);

        vector<vector<int>> parent(N, vector<int>(M + 1));
        for (int r = 0; r < N; ++r)
            for (int c = 0; c <= M; ++c) parent[r][c] = c;

        vector<int> row_parent(N + 1);
        for (int r = 0; r <= N; ++r) row_parent[r] = r;
        vector<int> row_rem(N, M);

        long long filled_total = 0;
        long long total = 1LL * N * M;

        for (int qi = Q - 1; qi >= 0; --qi) {
            if (filled_total >= total) break;
            int R = qs[qi].r;
            int C = qs[qi].c;
            int P = qs[qi].p;
            long long p2 = 1LL * P * P;

            int r1 = max(0, R - P);
            int r2 = min(N - 1, R + P);

            int r = find_par(row_parent, r1);
            while (r <= r2) {
                long long dx = (long long)r - R;
                long long rem = p2 - dx * dx;
                long long d = sqrtl((long double)rem);
                while ((d + 1) * (d + 1) <= rem) ++d;
                while (d * d > rem) --d;

                int L = max(0, C - (int)d);
                int Rr = min(M - 1, C + (int)d);

                vector<int> &par = parent[r];
                int c = find_par(par, L);
                while (c <= Rr) {
                    long long dc = (long long)c - C;
                    ans[(size_t)r * M + c] = p2 - dx * dx - dc * dc + 1;
                    ++filled_total;
                    --row_rem[r];
                    int nxt = find_par(par, c + 1);
                    par[c] = nxt;
                    c = nxt;
                }

                if (row_rem[r] == 0) {
                    row_parent[r] = find_par(row_parent, r + 1);
                    r = row_parent[r];
                } else {
                    r = find_par(row_parent, r + 1);
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << ans[(size_t)r * M + c];
            }
            cout << '\n';   // <- always, for every row
        }
    }
    return 0;
}