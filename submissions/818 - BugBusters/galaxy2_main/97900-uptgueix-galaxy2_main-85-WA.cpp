#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (int i = 0; i < N; i++) cin >> g[i];

        struct Query {
            int rs, cs, re, ce;
            long long K;
        };

        vector<Query> qs(Q);
        for (int i = 0; i < Q; i++) {
            cin >> qs[i].rs >> qs[i].cs >> qs[i].re
                >> qs[i].ce >> qs[i].K;
        }

        // Node ID: (mode * N + row) * M + column
        auto id = [&](int mode, int r, int c) {
            return (mode * N + r) * M + c;
        };

        auto active = [&](int mode, int r, int c) -> bool {
            char ch = g[r][c];
            if (ch == '.') return true;
            if (ch == 'B') return mode == 0;
            return mode == 1; // 'R'
        };

        int V = 2 * N * M;
        vector<int> dist(V);
        vector<int> que(V);

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        // BFS restricted to columns [cl, cr].
        auto bfs = [&](int src, int cl, int cr) {
            fill(dist.begin(), dist.end(), -1);

            int qh = 0, qt = 0;
            que[qt++] = src;
            dist[src] = 0;

            while (qh < qt) {
                int cur = que[qh++];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M;
                int c = rem % M;
                int d = dist[cur];

                // Spin is allowed only on '.' cells.
                if (g[r][c] == '.') {
                    int nid = id(1 - mode, r, c);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        que[qt++] = nid;
                    }
                }

                // Four-directional movement.
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < 0 || nr >= N || nc < cl || nc > cr)
                        continue;

                    if (!active(mode, nr, nc))
                        continue;

                    int nid = id(mode, nr, nc);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        que[qt++] = nid;
                    }
                }
            }
        };

        vector<int> ans(Q, INF);

        // Starting node of a query.
        auto startNode = [&](int i) {
            return id(0, qs[i].rs, qs[i].cs);
        };

        // Destination node(s) of a query.
        auto destNodes = [&](int i, int &t0, int &t1, bool &hasTwo) {
            char dch = g[qs[i].re][qs[i].ce];

            if (dch == 'R') {
                t0 = id(1, qs[i].re, qs[i].ce);
                hasTwo = false;
            } else if (dch == 'B') {
                t0 = id(0, qs[i].re, qs[i].ce);
                hasTwo = false;
            } else {
                t0 = id(0, qs[i].re, qs[i].ce);
                t1 = id(1, qs[i].re, qs[i].ce);
                hasTwo = true;
            }
        };

        // Iterative divide and conquer to avoid recursion.
        struct Task {
            int l, r;
            vector<int> idx;
        };

        vector<Task> st;
        vector<int> all(Q);
        iota(all.begin(), all.end(), 0);
        st.push_back({0, M - 1, move(all)});

        while (!st.empty()) {
            Task curTask = move(st.back());
            st.pop_back();

            int l = curTask.l;
            int r = curTask.r;
            auto &idx = curTask.idx;

            if (idx.empty()) continue;

            if (l == r) {
                // Only one column remains. Run BFS for each distinct start.
                sort(idx.begin(), idx.end(), [&](int a, int b) {
                    return startNode(a) < startNode(b);
                });

                for (size_t k = 0; k < idx.size();) {
                    size_t k2 = k;
                    int s = startNode(idx[k]);

                    bfs(s, l, r);

                    while (k2 < idx.size() && startNode(idx[k2]) == s) {
                        int qi = idx[k2];

                        int t0, t1 = -1;
                        bool hasTwo = false;
                        destNodes(qi, t0, t1, hasTwo);

                        int best = INF;
                        if (dist[t0] != -1)
                            best = dist[t0];

                        if (hasTwo && dist[t1] != -1)
                            best = min(best, dist[t1]);

                        ans[qi] = min(ans[qi], best);
                        k2++;
                    }

                    k = k2;
                }

                continue;
            }

            int mid = (l + r) / 2;

            // Portals are all active nodes in the middle column.
            vector<int> portals;

            for (int mode = 0; mode < 2; mode++) {
                for (int rr = 0; rr < N; rr++) {
                    if (active(mode, rr, mid))
                        portals.push_back(id(mode, rr, mid));
                }
            }

            int P = (int)portals.size();
            int SZ = (int)idx.size();

            // Store distances from each portal to each query's start
            // and destination.
            vector<vector<int>> DS(P, vector<int>(SZ, -1));
            vector<vector<int>> DT(P, vector<int>(SZ, -1));

            for (int p = 0; p < P; p++) {
                bfs(portals[p], l, r);

                for (int k = 0; k < SZ; k++) {
                    int qi = idx[k];
                    int s = startNode(qi);

                    int t0, t1 = -1;
                    bool hasTwo = false;
                    destNodes(qi, t0, t1, hasTwo);

                    DS[p][k] = dist[s];

                    int best = INF;
                    if (dist[t0] != -1)
                        best = dist[t0];

                    if (hasTwo && dist[t1] != -1)
                        best = min(best, dist[t1]);

                    DT[p][k] = (best == INF ? -1 : best);
                }
            }

            vector<int> leftIdx, rightIdx;
            leftIdx.reserve(SZ);
            rightIdx.reserve(SZ);

            for (int k = 0; k < SZ; k++) {
                int qi = idx[k];
                int cs = qs[qi].cs;
                int ce = qs[qi].ce;

                bool cross =
                    (cs <= mid && ce > mid) ||
                    (ce <= mid && cs > mid);

                if (cross) {
                    int best = INF;

                    for (int p = 0; p < P; p++) {
                        if (DS[p][k] != -1 && DT[p][k] != -1) {
                            best = min(best, DS[p][k] + DT[p][k]);
                        }
                    }

                    ans[qi] = min(ans[qi], best);
                } else if (ce <= mid && cs <= mid) {
                    leftIdx.push_back(qi);
                } else {
                    rightIdx.push_back(qi);
                }
            }

            if (!rightIdx.empty())
                st.push_back({mid + 1, r, move(rightIdx)});

            if (!leftIdx.empty())
                st.push_back({l, mid, move(leftIdx)});
        }

        for (int i = 0; i < Q; i++) {
            cout << (ans[i] <= qs[i].K ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
