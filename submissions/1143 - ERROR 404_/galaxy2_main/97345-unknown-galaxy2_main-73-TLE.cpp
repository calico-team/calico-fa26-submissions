#include <bits/stdc++.h>
using namespace std;

inline int id3(int r, int c, int mode, int N, int M) {
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
    const int INF = 1e9;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; ++i) cin >> g[i];
        struct Qry {int rs, cs, re, ce; long long K;};
        vector<Qry> qs(Q);
        for (int i = 0; i < Q; ++i) cin >> qs[i].rs >> qs[i].cs >> qs[i].re >> qs[i].ce >> qs[i].K;

        int TOT = 2 * N * M;
        vector<int> dist(TOT);
        vector<int> qbuf(TOT);
        auto bfs_single = [&](int sr, int sc, int sm) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            int s = id3(sr, sc, sm, N, M);
            dist[s] = 0;
            qbuf[qt++] = s;
            const int dr[4] = {1, -1, 0, 0};
            const int dc[4] = {0, 0, 1, -1};
            while (qh < qt) {
                int cur = qbuf[qh++];
                int d = dist[cur];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M, c = rem % M;
                if (g[r][c] == '.') {
                    int nm = 1 - mode;
                    int nid = id3(r, c, nm, N, M);
                    if (dist[nid] == -1) { dist[nid] = d + 1; qbuf[qt++] = nid; }
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!active_cell(g[nr][nc], mode)) continue;
                    int nid = id3(nr, nc, mode, N, M);
                    if (dist[nid] == -1) { dist[nid] = d + 1; qbuf[qt++] = nid; }
                }
            }
        };
        auto bfs_multi_dest = [&](int dr_, int dc_) {
            fill(dist.begin(), dist.end(), -1);
            int qh = 0, qt = 0;
            char ch = g[dr_][dc_];
            for (int mode = 0; mode < 2; ++mode) {
                if (!active_cell(ch, mode)) continue;
                int s = id3(dr_, dc_, mode, N, M);
                dist[s] = 0;
                qbuf[qt++] = s;
            }
            const int dr[4] = {1, -1, 0, 0};
            const int dc[4] = {0, 0, 1, -1};
            while (qh < qt) {
                int cur = qbuf[qh++];
                int d = dist[cur];
                int mode = cur / (N * M);
                int rem = cur % (N * M);
                int r = rem / M, c = rem % M;
                if (g[r][c] == '.') {
                    int nm = 1 - mode;
                    int nid = id3(r, c, nm, N, M);
                    if (dist[nid] == -1) { dist[nid] = d + 1; qbuf[qt++] = nid; }
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!active_cell(g[nr][nc], mode)) continue;
                    int nid = id3(nr, nc, mode, N, M);
                    if (dist[nid] == -1) { dist[nid] = d + 1; qbuf[qt++] = nid; }
                }
            }
        };

        vector<string> ans(Q);
        // group by start and by dest
        unordered_map<int, vector<int>> byStart, byDest;
        byStart.reserve(Q * 2);
        byDest.reserve(Q * 2);
        for (int i = 0; i < Q; ++i) {
            int ks = qs[i].rs * M + qs[i].cs;
            int kd = qs[i].re * M + qs[i].ce;
            byStart[ks].push_back(i);
            byDest[kd].push_back(i);
        }
        // BFS from the side with fewer distinct sources, with early stop per source
        // We implement per-source BFS with early exit: stop when all dests of this source found.
        if (byStart.size() <= byDest.size()) {
            for (auto &p : byStart) {
                int key = p.first;
                int sr = key / M, sc = key % M;
                // collect needed dest ids
                unordered_set<int> need;
                need.reserve(p.second.size()*2);
                for (int qi : p.second) {
                    char ch = g[qs[qi].re][qs[qi].ce];
                    if (ch == '.') { need.insert(id3(qs[qi].re, qs[qi].ce, 0, N, M)); need.insert(id3(qs[qi].re, qs[qi].ce, 1, N, M)); }
                    else if (ch == 'B') need.insert(id3(qs[qi].re, qs[qi].ce, 0, N, M));
                    else need.insert(id3(qs[qi].re, qs[qi].ce, 1, N, M));
                }
                // BFS with early stop
                fill(dist.begin(), dist.end(), -1);
                int qh = 0, qt = 0;
                int s = id3(sr, sc, 0, N, M);
                dist[s] = 0; qbuf[qt++] = s;
                int found = 0;
                if (need.count(s)) found++;
                const int dr[4] = {1, -1, 0, 0};
                const int dc[4] = {0, 0, 1, -1};
                while (qh < qt && found < (int)need.size()) {
                    int cur = qbuf[qh++];
                    int d = dist[cur];
                    int mode = cur / (N * M);
                    int rem = cur % (N * M);
                    int r = rem / M, c = rem % M;
                    auto push = [&](int nid) {
                        if (dist[nid] == -1) {
                            dist[nid] = d + 1;
                            qbuf[qt++] = nid;
                            if (need.count(nid)) found++;
                        }
                    };
                    if (g[r][c] == '.') push(id3(r, c, 1 - mode, N, M));
                    for (int k = 0; k < 4; ++k) {
                        int nr = r + dr[k], nc = c + dc[k];
                        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                        if (!active_cell(g[nr][nc], mode)) continue;
                        push(id3(nr, nc, mode, N, M));
                    }
                }
                for (int qi : p.second) {
                    char ch = g[qs[qi].re][qs[qi].ce];
                    int best = INF;
                    if (ch == '.') {
                        int d0 = dist[id3(qs[qi].re, qs[qi].ce, 0, N, M)];
                        int d1 = dist[id3(qs[qi].re, qs[qi].ce, 1, N, M)];
                        if (d0 != -1) best = min(best, d0);
                        if (d1 != -1) best = min(best, d1);
                    } else if (ch == 'B') {
                        int d0 = dist[id3(qs[qi].re, qs[qi].ce, 0, N, M)];
                        if (d0 != -1) best = d0;
                    } else {
                        int d1 = dist[id3(qs[qi].re, qs[qi].ce, 1, N, M)];
                        if (d1 != -1) best = d1;
                    }
                    ans[qi] = (best != INF && best <= qs[qi].K) ? "YES" : "NO";
                }
            }
        } else {
            for (auto &p : byDest) {
                int key = p.first;
                int dr_ = key / M, dc_ = key % M;
                // needed start ids
                unordered_set<int> need;
                need.reserve(p.second.size());
                for (int qi : p.second) need.insert(id3(qs[qi].rs, qs[qi].cs, 0, N, M));
                // multi-source BFS from dest
                fill(dist.begin(), dist.end(), -1);
                int qh = 0, qt = 0;
                char chd = g[dr_][dc_];
                for (int mode = 0; mode < 2; ++mode) if (active_cell(chd, mode)) {
                    int s = id3(dr_, dc_, mode, N, M);
                    dist[s] = 0; qbuf[qt++] = s;
                }
                int found = 0;
                for (int nid : need) if (dist[nid] != -1) found++;
                const int dr[4] = {1, -1, 0, 0};
                const int dc[4] = {0, 0, 1, -1};
                while (qh < qt && found < (int)need.size()) {
                    int cur = qbuf[qh++];
                    int d = dist[cur];
                    int mode = cur / (N * M);
                    int rem = cur % (N * M);
                    int r = rem / M, c = rem % M;
                    auto push = [&](int nid) {
                        if (dist[nid] == -1) {
                            dist[nid] = d + 1;
                            qbuf[qt++] = nid;
                            if (need.count(nid)) found++;
                        }
                    };
                    if (g[r][c] == '.') push(id3(r, c, 1 - mode, N, M));
                    for (int k = 0; k < 4; ++k) {
                        int nr = r + dr[k], nc = c + dc[k];
                        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                        if (!active_cell(g[nr][nc], mode)) continue;
                        push(id3(nr, nc, mode, N, M));
                    }
                }
                for (int qi : p.second) {
                    int d0 = dist[id3(qs[qi].rs, qs[qi].cs, 0, N, M)];
                    ans[qi] = (d0 != -1 && d0 <= qs[qi].K) ? "YES" : "NO";
                }
            }
        }
        for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
    }
    return 0;
}