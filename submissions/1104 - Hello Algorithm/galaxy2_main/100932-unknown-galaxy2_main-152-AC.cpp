#include <bits/stdc++.h>
using namespace std;

struct Query {
    int s, tBlue, tRed, c1, c2, k;
    bool good;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> a(N);
        for (auto &s : a) cin >> s;

        int V = 2 * N * M;

        auto id = [&](int r, int c, int mode) {
            return 2 * (c * N + r) + mode;
        };

        auto enabled = [&](int r, int c, int mode) {
            return a[r][c] == '.' || a[r][c] == (mode ? 'R' : 'B');
        };

        vector<array<int, 5>> nbr(V);
        vector<unsigned char> cnt(V, 0);

        auto add = [&](int u, int v) {
            nbr[u][cnt[u]++] = v;
            nbr[v][cnt[v]++] = u;
        };

        for (int c = 0; c < M; c++) {
            for (int r = 0; r < N; r++) {
                if (a[r][c] == '.')
                    add(id(r, c, 0), id(r, c, 1));

                for (int mode = 0; mode < 2; mode++) {
                    if (!enabled(r, c, mode))
                        continue;

                    int u = id(r, c, mode);

                    if (r > 0 && enabled(r - 1, c, mode))
                        add(u, id(r - 1, c, mode));

                    if (c > 0 && enabled(r, c - 1, mode))
                        add(u, id(r, c - 1, mode));
                }
            }
        }

        vector<Query> q(Q);
        vector<int> pending;

        for (int i = 0; i < Q; i++) {
            int sr, sc, tr, tc, k;
            cin >> sr >> sc >> tr >> tc >> k;

            q[i] = {
                id(sr, sc, 0),
                enabled(tr, tc, 0) ? id(tr, tc, 0) : -1,
                enabled(tr, tc, 1) ? id(tr, tc, 1) : -1,
                sc, tc, k, false
            };

            if (sr == tr && sc == tc)
                q[i].good = true;
            else if (abs(sr - tr) + abs(sc - tc) <= k)
                pending.push_back(i);
        }

        vector<int> mark(V, 0), dist(V), bfsQueue(V);
        int tick = 0;

        function<void(int, int, vector<int>&&)> solve =
        [&](int left, int right, vector<int>&& ids) {
            if (ids.empty()) return;

            int mid = (left + right) / 2;

            for (int r = 0; r < N; r++) {
                for (int mode = 0; mode < 2; mode++) {
                    if (!enabled(r, mid, mode))
                        continue;

                    int s = id(r, mid, mode);
                    tick++;

                    int front = 0, back = 0;
                    bfsQueue[back++] = s;
                    mark[s] = tick;
                    dist[s] = 0;

                    while (front < back) {
                        int u = bfsQueue[front++];

                        for (int j = 0; j < cnt[u]; j++) {
                            int v = nbr[u][j];
                            int c = v / (2 * N);

                            if (c < left || c > right ||
                                mark[v] == tick)
                                continue;

                            mark[v] = tick;
                            dist[v] = dist[u] + 1;
                            bfsQueue[back++] = v;
                        }
                    }

                    for (int idx : ids) {
                        auto &t = q[idx];

                        if (t.good || mark[t.s] != tick)
                            continue;

                        if ((t.tBlue != -1 &&
                             mark[t.tBlue] == tick &&
                             dist[t.s] + dist[t.tBlue] <= t.k) ||
                            (t.tRed != -1 &&
                             mark[t.tRed] == tick &&
                             dist[t.s] + dist[t.tRed] <= t.k)) {
                            t.good = true;
                        }
                    }
                }
            }

            if (left == right) return;

            vector<int> lq, rq;

            for (int idx : ids) {
                auto &t = q[idx];

                if (t.good) continue;

                if (t.c1 < mid && t.c2 < mid)
                    lq.push_back(idx);
                else if (t.c1 > mid && t.c2 > mid)
                    rq.push_back(idx);
            }

            if (!lq.empty())
                solve(left, mid - 1, move(lq));

            if (!rq.empty())
                solve(mid + 1, right, move(rq));
        };

        solve(0, M - 1, move(pending));

        for (auto &t : q)
            cout << (t.good ? "YES" : "NO") << '\n';
    }

    return 0;
}
