#include <bits/stdc++.h>
using namespace std;

struct Query {
    int s, t0, t1, a, b, k;
    bool ok = false;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (auto &s : g) cin >> s;

        int V = 2 * N * M;
        vector<vector<int>> adj(V);

        auto id = [&](int r, int c, int mode) {
            return 2 * (c * N + r) + mode;
        };

        auto valid = [&](int r, int c, int mode) {
            return g[r][c] == '.' ||
                   g[r][c] == (mode ? 'R' : 'B');
        };

        auto link = [&](int a, int b) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        };

        for (int c = 0; c < M; c++) {
            for (int r = 0; r < N; r++) {
                if (g[r][c] == '.')
                    link(id(r, c, 0), id(r, c, 1));

                for (int mode = 0; mode < 2; mode++) {
                    if (!valid(r, c, mode)) continue;

                    if (r + 1 < N && valid(r + 1, c, mode))
                        link(id(r, c, mode), id(r + 1, c, mode));

                    if (c + 1 < M && valid(r, c + 1, mode))
                        link(id(r, c, mode), id(r, c + 1, mode));
                }
            }
        }

        vector<Query> queries(Q);
        vector<int> active;

        for (int i = 0; i < Q; i++) {
            int sr, sc, tr, tc, k;
            cin >> sr >> sc >> tr >> tc >> k;

            auto &v = queries[i];

            v.s = id(sr, sc, 0);
            v.t0 = valid(tr, tc, 0) ? id(tr, tc, 0) : -1;
            v.t1 = valid(tr, tc, 1) ? id(tr, tc, 1) : -1;
            v.a = sc;
            v.b = tc;
            v.k = k;

            if (sr == tr && sc == tc)
                v.ok = true;
            else
                active.push_back(i);
        }

        vector<int> seen(V, 0), dist(V), que(V);
        int stamp = 0;

        function<void(int, int, vector<int>&)> run =
        [&](int l, int r, vector<int>& ids) {
            if (ids.empty()) return;

            int mid = (l + r) / 2;

            for (int row = 0; row < N; row++) {
                for (int mode = 0; mode < 2; mode++) {
                    if (!valid(row, mid, mode)) continue;

                    int source = id(row, mid, mode);
                    ++stamp;

                    int head = 0, tail = 1;
                    que[0] = source;
                    seen[source] = stamp;
                    dist[source] = 0;

                    while (head < tail) {
                        int u = que[head++];
                        int nd = dist[u] + 1;

                        for (int v : adj[u]) {
                            if (seen[v] == stamp) continue;

                            int col = v / (2 * N);
                            if (col < l || col > r) continue;

                            seen[v] = stamp;
                            dist[v] = nd;
                            que[tail++] = v;
                        }
                    }

                    for (int idx : ids) {
                        auto &a = queries[idx];

                        if (a.ok || seen[a.s] != stamp)
                            continue;

                        int d0 = INT_MAX / 4;
                        int d1 = INT_MAX / 4;

                        if (a.t0 >= 0 && seen[a.t0] == stamp)
                            d0 = dist[a.t0];

                        if (a.t1 >= 0 && seen[a.t1] == stamp)
                            d1 = dist[a.t1];

                        if (dist[a.s] + min(d0, d1) <= a.k)
                            a.ok = true;
                    }
                }
            }

            if (l == r) return;

            vector<int> left, right;

            for (int idx : ids) {
                const auto &a = queries[idx];

                if (a.ok) continue;

                if (a.a < mid && a.b < mid)
                    left.push_back(idx);
                else if (a.a > mid && a.b > mid)
                    right.push_back(idx);
            }

            if (l < mid)
                run(l, mid - 1, left);

            if (mid < r)
                run(mid + 1, r, right);
        };

        run(0, M - 1, active);

        for (const auto &a : queries)
            cout << (a.ok ? "YES" : "NO") << '\n';
    }

    return 0;
}
