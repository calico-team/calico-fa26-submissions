#include <bits/stdc++.h>
using namespace std;
const int INF_INT = 1e9;
const long long INF_LL = (long long)4e18;

inline int idx3(int r, int c, int mode, int N, int M) {
    return (mode * N + r) * M + c;
}
inline bool active_cell(char ch, int mode) {
    if (ch == '.') return true;
    if (mode == 0) return ch == 'B';
    return ch == 'R';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; ++i) cin >> g[i];
        struct Query {int rs, cs, re, ce; long long K;};
        vector<Query> qs(Q);
        for (int i = 0; i < Q; ++i) cin >> qs[i].rs >> qs[i].cs >> qs[i].re >> qs[i].ce >> qs[i].K;

        int W = 100;
        int nb = (M + W - 1) / W;
        auto block_of = [&](int c){ return c / W; };

        vector<long long> bestVia(Q, INF_LL);
        unordered_map<int, vector<int>> needCut;
        needCut.reserve(nb * 2);
        vector<int> isSame(Q, 0);
        for (int i = 0; i < Q; ++i) {
            int bs = block_of(qs[i].cs);
            int be = block_of(qs[i].ce);
            if (bs != be) {
                int cut = (bs + 1) * W;
                needCut[cut].push_back(i);
                isSame[i] = 0;
            } else {
                isSame[i] = 1;
                if (bs > 0) needCut[bs * W].push_back(i);
                if (be + 1 < nb) needCut[(be + 1) * W].push_back(i);
            }
        }

        int TOT = 2 * N * M;
        vector<int> dist(TOT);
        vector<int> qq(TOT);

        auto bfs_all = [&](int sr, int sc, int sm) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            int s = idx3(sr, sc, sm, N, M);
            dist[s] = 0;
            qq[qt++] = s;
            const int dr[4] = {1, -1, 0, 0};
            const int dc[4] = {0, 0, 1, -1};
            while (qh < qt) {
                int cur = qq[qh++];
                int d = dist[cur];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M;
                int c = rem % M;
                if (g[r][c] == '.') {
                    int nm = 1 - mode;
                    int nid = idx3(r, c, nm, N, M);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!active_cell(g[nr][nc], mode)) continue;
                    int nid = idx3(nr, nc, mode, N, M);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
            }
        };

        // process cuts
        for (auto &p : needCut) {
            int cut = p.first;
            vector<int> &qlist = p.second;
            // cut nodes at column cut
            struct CN {int r, c, mode;};
            vector<CN> cnodes;
            for (int r = 0; r < N; ++r) {
                for (int mode = 0; mode < 2; ++mode) {
                    if (active_cell(g[r][cut], mode)) cnodes.push_back({r, cut, mode});
                }
            }
            if (cnodes.empty()) continue;
            unordered_map<int,long long> bestThis;
            bestThis.reserve(qlist.size()*2);
            for (int qi : qlist) bestThis[qi] = INF_LL;
            // For fast lookup, we need qlist as vector (may have duplicates because same query needs two cuts)
            // bestThis is per cut, duplicates are fine (same qi appears once in this list? it can appear twice if both cuts same? no)
            for (auto cn : cnodes) {
                bfs_all(cn.r, cn.c, cn.mode);
                for (int qi : qlist) {
                    int ds = dist[idx3(qs[qi].rs, qs[qi].cs, 0, N, M)];
                    if (ds == -1) continue;
                    char ch = g[qs[qi].re][qs[qi].ce];
                    long long best = INF_LL;
                    if (ch == '.') {
                        int d0 = dist[idx3(qs[qi].re, qs[qi].ce, 0, N, M)];
                        int d1 = dist[idx3(qs[qi].re, qs[qi].ce, 1, N, M)];
                        if (d0 != -1) best = min(best, (long long)ds + d0);
                        if (d1 != -1) best = min(best, (long long)ds + d1);
                    } else if (ch == 'B') {
                        int d0 = dist[idx3(qs[qi].re, qs[qi].ce, 0, N, M)];
                        if (d0 != -1) best = (long long)ds + d0;
                    } else {
                        int d1 = dist[idx3(qs[qi].re, qs[qi].ce, 1, N, M)];
                        if (d1 != -1) best = (long long)ds + d1;
                    }
                    auto it = bestThis.find(qi);
                    if (it != bestThis.end() && best < it->second) it->second = best;
                }
            }
            for (int qi : qlist) {
                auto it = bestThis.find(qi);
                if (it != bestThis.end()) bestVia[qi] = min(bestVia[qi], it->second);
            }
        }

        vector<long long> answer(Q, INF_LL);
        for (int i = 0; i < Q; ++i) if (!isSame[i]) answer[i] = bestVia[i];

        // same-block queries: grouped restricted BFS by (block, start)
        struct GroupKey {int block, sr, sc;};
        struct Group { vector<int> qs; };
        map<tuple<int,int,int>, vector<int>> groups;
        for (int i = 0; i < Q; ++i) if (isSame[i]) {
            int b = block_of(qs[i].cs);
            groups[{b, qs[i].rs, qs[i].cs}].push_back(i);
        }
        // BFS restricted helper
        auto bfs_restricted = [&](int sr, int sc, int sm, int c_low, int c_high) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            int s = idx3(sr, sc, sm, N, M);
            dist[s] = 0;
            qq[qt++] = s;
            const int dr[4] = {1, -1, 0, 0};
            const int dc[4] = {0, 0, 1, -1};
            while (qh < qt) {
                int cur = qq[qh++];
                int d = dist[cur];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M;
                int c = rem % M;
                if (g[r][c] == '.') {
                    int nm = 1 - mode;
                    int nid = idx3(r, c, nm, N, M);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < c_low || nc > c_high) continue;
                    if (!active_cell(g[nr][nc], mode)) continue;
                    int nid = idx3(nr, nc, mode, N, M);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        qq[qt++] = nid;
                    }
                }
            }
        };

        for (auto &gp : groups) {
            int b, sr, sc;
            tie(b, sr, sc) = gp.first;
            int c_low = b * W;
            int c_high = min(M - 1, (b + 1) * W - 1);
            bfs_restricted(sr, sc, 0, c_low, c_high);
            for (int qi : gp.second) {
                long long best = bestVia[qi];
                char ch = g[qs[qi].re][qs[qi].ce];
                long long rd = INF_LL;
                if (ch == '.') {
                    int d0 = dist[idx3(qs[qi].re, qs[qi].ce, 0, N, M)];
                    int d1 = dist[idx3(qs[qi].re, qs[qi].ce, 1, N, M)];
                    if (d0 != -1) rd = min(rd, (long long)d0);
                    if (d1 != -1) rd = min(rd, (long long)d1);
                } else if (ch == 'B') {
                    int d0 = dist[idx3(qs[qi].re, qs[qi].ce, 0, N, M)];
                    if (d0 != -1) rd = d0;
                } else {
                    int d1 = dist[idx3(qs[qi].re, qs[qi].ce, 1, N, M)];
                    if (d1 != -1) rd = d1;
                }
                best = min(best, rd);
                answer[qi] = best;
            }
        }

        for (int i = 0; i < Q; ++i) {
            cout << (answer[i] <= qs[i].K ? "YES\n" : "NO\n");
        }
    }
    return 0;
}