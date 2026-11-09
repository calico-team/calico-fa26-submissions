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
        struct Query {int rs, cs, re, ce; long long K;};
        vector<Query> qs(Q);
        for (int i = 0; i < Q; i++)
            cin >> qs[i].rs >> qs[i].cs >> qs[i].re >> qs[i].ce >> qs[i].K;

        int V = 2 * N * M;
        auto id = [&](int mode, int r, int c) {
            return (mode * N + r) * M + c;
        };
        auto active = [&](int mode, int r, int c) -> bool {
            char ch = g[r][c];
            if (ch == '.') return true;
            if (ch == 'B') return mode == 0;
            return mode == 1; // 'R'
        };

        // BFS, restricted to optional column range [cl, cr].
        vector<int> dist(V);
        vector<int> qq(V);
        auto bfs = [&](int src, int cl, int cr) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            qq[qt++] = src;
            dist[src] = 0;
            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};
            while (qh < qt) {
                int cur = qq[qh++];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M, c = rem % M;
                int d = dist[cur];

                // Spin at a normal tile.
                if (g[r][c] == '.') {
                    int nid = id(1 - mode, r, c);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }

                // Move in four directions.
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < cl || nc > cr) continue;
                    if (!active(mode, nr, nc)) continue;
                    int nid = id(mode, nr, nc);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
            }
        };

        vector<int> ans(Q, INF);

        // Blocks and cuts.
        const int B = 350;
        int nb = (M + B - 1) / B;
        vector<int> blockL(nb), blockR(nb);
        for (int b = 0; b < nb; b++) {
            blockL[b] = b * B;
            blockR[b] = min(M - 1, (b + 1) * B - 1);
        }

        // For every cut, run BFS from nodes in its two boundary columns.
        for (int b = 0; b + 1 < nb; b++) {
            int cutCols[2] = {blockR[b], blockL[b + 1]};
            for (int ci = 0; ci < 2; ci++) {
                int cc = cutCols[ci];
                for (int mode = 0; mode < 2; mode++) {
                    for (int r = 0; r < N; r++) {
                        if (!active(mode, r, cc)) continue;
                        int src = id(mode, r, cc);
                        bfs(src, 0, M - 1);

                        for (int i = 0; i < Q; i++) {
                            int cs = qs[i].cs, ce = qs[i].ce;
                            int left = min(cs, ce), right = max(cs, ce);
                            if (left > blockR[b] || right < blockL[b + 1])
                                continue;

                            int s = id(0, qs[i].rs, qs[i].cs);
                            int t = id(0, qs[i].re, qs[i].ce);
                            char dch = g[qs[i].re][qs[i].ce];

                            int best = INF;
                            if (dch == '.') {
                                int t1 = id(1, qs[i].re, qs[i].ce);
                                if (dist[s] != -1 && dist[t1] != -1)
                                    best = min(best, dist[s] + dist[t1]);
                            }
                            if (dist[s] != -1 && dist[t] != -1)
                                best = min(best, dist[s] + dist[t]);

                            ans[i] = min(ans[i], best);
                        }
                    }
                }
            }
        }

        // Queries whose start and end are in the same block.
        for (int i = 0; i < Q; i++) {
            int bs = qs[i].cs / B;
            int be = qs[i].ce / B;
            if (bs != be) continue;

            int src = id(0, qs[i].rs, qs[i].cs);
            bfs(src, blockL[bs], blockR[bs]);

            char dch = g[qs[i].re][qs[i].ce];
            int t0 = id(0, qs[i].re, qs[i].ce);
            int best = INF;

            if (dist[t0] != -1) best = dist[t0];

            if (dch == '.') {
                int t1 = id(1, qs[i].re, qs[i].ce);
                if (dist[t1] != -1) best = min(best, dist[t1]);
            }

            ans[i] = min(ans[i], best);
        }

        for (int i = 0; i < Q; i++) {
            cout << (ans[i] <= qs[i].K ? "YES" : "NO") << '\\n';
        }
    }

    return 0;
}