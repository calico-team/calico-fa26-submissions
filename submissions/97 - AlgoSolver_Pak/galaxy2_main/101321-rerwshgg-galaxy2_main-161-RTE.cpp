#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    const int BSIZE = 80;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; i++) cin >> g[i];

        auto validState = [&](int r, int c, int mode) -> bool {
            char ch = g[r][c];
            if (ch == '.') return true;
            if (ch == 'R') return mode == 1;
            return mode == 0; // 'B'
        };
        auto stateId = [&](int r, int c, int mode) {
            return ((r * M + c) * 2 + mode);
        };
        int S = N * M * 2;
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        vector<int> dist(S);
        vector<int> qq(S);
        auto bfs_full = [&](int src, vector<int> &out) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            qq[qt++] = src;
            dist[src] = 0;
            while (qh < qt) {
                int cur = qq[qh++];
                int mode = cur & 1;
                int tmp = cur >> 1;
                int c = tmp % M;
                int r = tmp / M;
                int d = dist[cur];
                if (g[r][c] == '.') {
                    int nid = cur ^ 1;
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
                for (int dir = 0; dir < 4; dir++) {
                    int nr = r + dr[dir], nc = c + dc[dir];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!validState(nr, nc, mode)) continue;
                    int nid = stateId(nr, nc, mode);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
            }
            out = dist;
        };

        // ---- blocks & portals ----
        vector<int> bounds;
        for (int c = 0; c < M; c += BSIZE) bounds.push_back(c);
        if (bounds.back() != M - 1) bounds.push_back(M - 1);
        int Bcnt = (int)bounds.size() - 1;

        vector<int> portalNode;
        vector<vector<int>> boundPortals(bounds.size());
        for (size_t bi = 0; bi < bounds.size(); bi++) {
            int c = bounds[bi];
            for (int r = 0; r < N; r++)
                for (int mode = 0; mode < 2; mode++) {
                    if (!validState(r, c, mode)) continue;
                    int pid = (int)portalNode.size();
                    portalNode.push_back(stateId(r, c, mode));
                    boundPortals[bi].push_back(pid);
                }
        }
        int P = (int)portalNode.size();
        vector<vector<int>> blockPortals(Bcnt);
        for (int i = 0; i < Bcnt; i++) {
            blockPortals[i].insert(blockPortals[i].end(),
                boundPortals[i].begin(), boundPortals[i].end());
            blockPortals[i].insert(blockPortals[i].end(),
                boundPortals[i + 1].begin(), boundPortals[i + 1].end());
        }

        vector<vector<int>> portalDist(P, vector<int>(S, -1));
        vector<int> tmp;
        for (int p = 0; p < P; p++) bfs_full(portalNode[p], portalDist[p]);

        auto blockOf = [&](int c) {
            int idx = (int)(upper_bound(bounds.begin(), bounds.end(), c) - bounds.begin()) - 1;
            if (idx < 0) idx = 0;
            if (idx >= Bcnt) idx = Bcnt - 1;
            return idx;
        };

        struct Query { int sr, sc, er, ec, K; };
        vector<Query> queries(Q);
        for (int i = 0; i < Q; i++)
            cin >> queries[i].sr >> queries[i].sc >> queries[i].er >> queries[i].ec >> queries[i].K;

        // ---- cache for same-block BFS ----
        // cache[block][localStartState] = distances inside block, empty = not computed
        vector<vector<vector<int>>> cache(Bcnt);
        vector<vector<char>> cacheDone(Bcnt);
        for (int b = 0; b < Bcnt; b++) {
            int bl = bounds[b], br = bounds[b + 1];
            int W = br - bl + 1;
            int BS = N * W * 2;
            cache[b].assign(BS, {});
            cacheDone[b].assign(BS, 0);
        }

        auto getBlockDist = [&](int b, int startNode) -> const vector<int>& {
            int bl = bounds[b], br = bounds[b + 1];
            int W = br - bl + 1;
            int mode0 = startNode & 1;
            int tmp0 = startNode >> 1;
            int sc0 = tmp0 % M, sr0 = tmp0 / M;
            int localStart = ((sr0 * W + (sc0 - bl)) * 2 + mode0);
            if (cacheDone[b][localStart]) return cache[b][localStart];

            int BS = N * W * 2;
            vector<int> d(BS, -1);
            vector<int> qq2(BS);
            int qh = 0, qt = 0;
            qq2[qt++] = localStart;
            d[localStart] = 0;
            auto lid = [&](int r, int c, int mode) {
                return ((r * W + (c - bl)) * 2 + mode);
            };
            while (qh < qt) {
                int cur = qq2[qh++];
                int mode = cur & 1;
                int tt = cur >> 1;
                int cc = tt % W;
                int rr = tt / W;
                int c = cc + bl;
                int dd = d[cur];
                if (g[rr][c] == '.') {
                    int nid = cur ^ 1;
                    if (d[nid] == -1) { d[nid] = dd + 1; qq2[qt++] = nid; }
                }
                for (int dir = 0; dir < 4; dir++) {
                    int nr = rr + dr[dir], nc = c + dc[dir];
                    if (nr < 0 || nr >= N || nc < bl || nc > br) continue;
                    if (!validState(nr, nc, mode)) continue;
                    int nid = lid(nr, nc, mode);
                    if (d[nid] == -1) { d[nid] = dd + 1; qq2[qt++] = nid; }
                }
            }
            cache[b][localStart] = std::move(d);
            cacheDone[b][localStart] = 1;
            return cache[b][localStart];
        };

        for (auto &qu : queries) {
            int startNode = stateId(qu.sr, qu.sc, 0); // start hamesha blue
            int bS = blockOf(qu.sc);
            int bE = blockOf(qu.ec);
            int best = INF;

            // end nodes
            int endNodes[2], endCnt = 0;
            for (int mode = 0; mode < 2; mode++)
                if (validState(qu.er, qu.ec, mode))
                    endNodes[endCnt++] = stateId(qu.er, qu.ec, mode);

            // via start-block portal: O(40) per query
            for (int p : blockPortals[bS]) {
                int d1 = portalDist[p][startNode];
                if (d1 == -1) continue;
                int bestD2 = INF;
                for (int i = 0; i < endCnt; i++) {
                    int d2 = portalDist[p][endNodes[i]];
                    if (d2 != -1) bestD2 = min(bestD2, d2);
                }
                if (bestD2 == INF) continue;
                best = min(best, d1 + bestD2);
            }

            // same block: andar rehne wala rasta (cached)
            if (bS == bE) {
                const vector<int> &d = getBlockDist(bS, startNode);
                int bl = bounds[bS];
                int W = bounds[bS + 1] - bl + 1;
                for (int i = 0; i < endCnt; i++) {
                    int mode = endNodes[i] & 1;
                    int tt = endNodes[i] >> 1;
                    int ec = tt % M, er = tt / M;
                    int lid = ((er * W + (ec - bl)) * 2 + mode);
                    if (lid >= 0 && lid < (int)d.size() && d[lid] != -1)
                        best = min(best, d[lid]);
                }
            }

            cout << (best <= qu.K ? "YES\n" : "NO\n");
        }
    }
    return 0;
}