#include<bits/stdc++.h>
using namespace std;
int main() {
    int T;
    if (!(cin >> T)) return 0;
    string out;
    out.reserve(1 << 16);
    const int INF = 100000000;
    const long long BFS_BUDGET = 30000000LL;
    vector<int> adjStart, adj, que, compOf, compSize;
    vector<int> qr1, qc1, qr2, qc2, qlo, qhi;
    vector<long long> qK;
    vector<char> ansFlag, settled;
    vector<int> matP, matG, curM, sufM, dist1, stamp;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int r = 0; r < N; ++r) cin >> g[r];

        const int S2 = 2 * N;                       // 一列内的状态数
        const int V = S2 * M;
        auto sid = [&](int r, int c, int md) -> int { return ((r * M + c) << 1) | md; };
        auto act = [&](int r, int c, int md) -> bool {
            const char ch = g[r][c];
            return ch == '.' ? true : (md == 0 ? ch == 'B' : ch == 'R');
        };

        // ---------------- 读入查询 ----------------
        qr1.resize(Q); qc1.resize(Q); qr2.resize(Q); qc2.resize(Q);
        qlo.resize(Q); qhi.resize(Q); qK.resize(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> qr1[i] >> qc1[i] >> qr2[i] >> qc2[i] >> qK[i];
            qlo[i] = min(qc1[i], qc2[i]);
            qhi[i] = max(qc1[i], qc2[i]);
        }

        // ---------------- 建无向图（CSR） ----------------
        vector<int> deg(V, 0);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                for (int md = 0; md < 2; ++md) {
                    if (!act(r, c, md)) continue;
                    int d = 0;
                    if (r > 0 && act(r - 1, c, md)) ++d;
                    if (r + 1 < N && act(r + 1, c, md)) ++d;
                    if (c > 0 && act(r, c - 1, md)) ++d;
                    if (c + 1 < M && act(r, c + 1, md)) ++d;
                    if (g[r][c] == '.') ++d;
                    deg[sid(r, c, md)] = d;
                }
            }
        }
        adjStart.assign(V + 1, 0);
        for (int i = 0; i < V; ++i) adjStart[i + 1] = adjStart[i] + deg[i];
        adj.assign(adjStart[V], 0);
        {
            vector<int> pos(adjStart.begin(), adjStart.end() - 1);
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < M; ++c) {
                    for (int md = 0; md < 2; ++md) {
                        if (!act(r, c, md)) continue;
                        const int v = sid(r, c, md);
                        if (r + 1 < N && act(r + 1, c, md)) {
                            const int u = sid(r + 1, c, md);
                            adj[pos[v]++] = u;
                            adj[pos[u]++] = v;
                        }
                        if (c + 1 < M && act(r, c + 1, md)) {
                            const int u = sid(r, c + 1, md);
                            adj[pos[v]++] = u;
                            adj[pos[u]++] = v;
                        }
                    }
                    if (g[r][c] == '.') {           // 自旋边
                        const int a = sid(r, c, 0), b = sid(r, c, 1);
                        adj[pos[a]++] = b;
                        adj[pos[b]++] = a;
                    }
                }
            }
        }

        // ---------------- 连通块 ----------------
        compOf.assign(V, -1);
        compSize.clear();
        que.assign(V, 0);
        for (int i = 0; i < V; ++i) {
            if (compOf[i] >= 0 || deg[i] == 0) continue;
            const int cid = (int)compSize.size();
            int head = 0, tail = 0, cnt = 0;
            compOf[i] = cid;
            que[tail++] = i;
            while (head < tail) {
                const int v = que[head++];
                ++cnt;
                for (int e = adjStart[v]; e < adjStart[v + 1]; ++e) {
                    const int u = adj[e];
                    if (compOf[u] < 0) {
                        compOf[u] = cid;
                        que[tail++] = u;
                    }
                }
            }
            compSize.push_back(cnt);
        }

        // ---------------- 前四级剪枝 ----------------
        ansFlag.assign(Q, 0);
        settled.assign(Q, 0);
        vector<int> cand, sameCol;
        cand.reserve(Q);
        sameCol.reserve(Q);

        for (int i = 0; i < Q; ++i) {
            const int rs = qr1[i], cs = qc1[i], re = qr2[i], ce = qc2[i];
            if (rs == re && cs == ce) { ansFlag[i] = 1; settled[i] = 1; continue; }

            int tComp = -1;
            if (g[re][ce] != 'R') tComp = compOf[sid(re, ce, 0)];
            if (tComp < 0 && g[re][ce] != 'B') tComp = compOf[sid(re, ce, 1)];
            const int comp = compOf[sid(rs, cs, 0)];

            if (comp < 0 || comp != tComp) { ansFlag[i] = 0; settled[i] = 1; continue; }
            if (qK[i] >= (long long)compSize[comp] - 1) { ansFlag[i] = 1; settled[i] = 1; continue; }
            if (qK[i] < (long long)abs(rs - re) + abs(cs - ce)) { ansFlag[i] = 0; settled[i] = 1; continue; }

            if (cs == ce) sameCol.push_back(i);
            else cand.push_back(i);
        }

        // ---------------- 同列查询：前缀 / 后缀闭包矩阵 ----------------
        // 两端都在第 c 列时，把路径按「每次回到第 c 列」切开，每段要么整段落在
        // 前缀 0..c、要么整段落在后缀 c..M-1，故全图距离 = Floyd(min(前缀, 后缀))。
        if (!sameCol.empty() && (long long)M * S2 * S2 <= 8000000LL) {
            const int tot = S2 * S2;

            auto floyd = [&](int* D) {
                for (int k = 0; k < S2; ++k) {
                    const int* Dk = D + k * S2;
                    for (int i = 0; i < S2; ++i) {
                        int* Di = D + i * S2;
                        const int dik = Di[k];
                        if (dik >= INF) continue;
                        for (int j = 0; j < S2; ++j) {
                            const int v = dik + Dk[j];
                            if (v < Di[j]) Di[j] = v;
                        }
                    }
                }
            };
            auto inCol = [&](int c, int* D) {       // 本列的竖边 + 自旋边
                for (int i = 0; i < tot; ++i) D[i] = INF;
                for (int i = 0; i < S2; ++i) D[i * S2 + i] = 0;
                for (int r = 0; r < N; ++r) {
                    for (int md = 0; md < 2; ++md) {
                        if (!act(r, c, md)) continue;
                        const int i = r * 2 + md;
                        if (r + 1 < N && act(r + 1, c, md)) {
                            const int j = (r + 1) * 2 + md;
                            D[i * S2 + j] = 1;
                            D[j * S2 + i] = 1;
                        }
                        if (g[r][c] == '.') D[i * S2 + (i ^ 1)] = 1;
                    }
                }
            };

            matP.assign((size_t)M * tot, 0);        // 前缀内、第 c 列状态间最短路
            matG.assign((size_t)M * tot, 0);        // 全图内、第 c 列状态间最短路
            curM.assign(tot, 0);
            sufM.assign(tot, 0);

            for (int c = 0; c < M; ++c) {
                inCol(c, curM.data());
                if (c > 0) {
                    const int* Pprev = &matP[(size_t)(c - 1) * tot];
                    for (int p = 0; p < S2; ++p) {
                        const int rp = p >> 1, mp = p & 1;
                        if (!act(rp, c, mp) || !act(rp, c - 1, mp)) continue;
                        for (int q = 0; q < S2; ++q) {
                            const int rq = q >> 1, mq = q & 1;
                            if (!act(rq, c, mq) || !act(rq, c - 1, mq)) continue;
                            const int v = Pprev[p * S2 + q];
                            if (v < INF && v + 2 < curM[p * S2 + q]) curM[p * S2 + q] = v + 2;
                        }
                    }
                }
                floyd(curM.data());
                copy(curM.begin(), curM.end(), matP.begin() + (size_t)c * tot);
            }

            for (int c = M - 1; c >= 0; --c) {
                inCol(c, sufM.data());
                if (c + 1 < M) {                    // curM 此时是后缀 c+1 的矩阵
                    for (int p = 0; p < S2; ++p) {
                        const int rp = p >> 1, mp = p & 1;
                        if (!act(rp, c, mp) || !act(rp, c + 1, mp)) continue;
                        for (int q = 0; q < S2; ++q) {
                            const int rq = q >> 1, mq = q & 1;
                            if (!act(rq, c, mq) || !act(rq, c + 1, mq)) continue;
                            const int v = curM[p * S2 + q];
                            if (v < INF && v + 2 < sufM[p * S2 + q]) sufM[p * S2 + q] = v + 2;
                        }
                    }
                }
                floyd(sufM.data());
                int* Gc = &matG[(size_t)c * tot];
                const int* Pc = &matP[(size_t)c * tot];
                for (int i = 0; i < tot; ++i) Gc[i] = min(Pc[i], sufM[i]);
                floyd(Gc);
                copy(sufM.begin(), sufM.end(), curM.begin());
            }

            for (int i : sameCol) {
                const int* Gc = &matG[(size_t)qc1[i] * tot];
                const int li = qr1[i] * 2;          // 起点必为 '.'，从模式 0 出发
                int best = INF;
                for (int md = 0; md < 2; ++md) {
                    if (md == 0 && g[qr2[i]][qc2[i]] == 'R') continue;
                    if (md == 1 && g[qr2[i]][qc2[i]] == 'B') continue;
                    const int v = Gc[li * S2 + (qr2[i] * 2 + md)];
                    if (v < best) best = v;
                }
                ansFlag[i] = (best <= qK[i]) ? 1 : 0;
                settled[i] = 1;
            }
        } else {
            for (int i : sameCol) cand.push_back(i);
        }
        if (!cand.empty()) {
            const long long colCost = (long long)S2 * V;
            long long stepsLeft = BFS_BUDGET;

            vector<int> diff(M + 1, 0);
            vector<int> distBuf((size_t)S2 * V, -1);
            int* dptr = distBuf.data();
            vector<int> rem = cand, nxt;
            nxt.reserve(cand.size());

            while (!rem.empty() && stepsLeft >= colCost) {
                fill(diff.begin(), diff.end(), 0);
                for (int i : rem) { ++diff[qlo[i]]; --diff[qhi[i] + 1]; }
                int bestC = -1, bestCnt = 0, run = 0;
                for (int c = 0; c < M; ++c) {
                    run += diff[c];
                    if (run > bestCnt) { bestCnt = run; bestC = c; }
                }
                if (bestC < 0 || bestCnt < S2 / 2) break;   // 覆盖太少，逐查询 BFS 更省

                const int col = bestC;
                int srcCnt = 0;
                for (int r = 0; r < N; ++r) {
                    for (int md = 0; md < 2; ++md) {
                        if (!act(r, col, md)) continue;
                        const int src = sid(r, col, md);
                        int* d = dptr + (size_t)srcCnt * V;
                        for (int i = 0; i < V; ++i) d[i] = -1;
                        int head = 0, tail = 0;
                        d[src] = 0;
                        que[tail++] = src;
                        while (head < tail) {
                            const int v = que[head++];
                            const int nd = d[v] + 1;
                            for (int e = adjStart[v]; e < adjStart[v + 1]; ++e) {
                                const int u = adj[e];
                                if (d[u] < 0) { d[u] = nd; que[tail++] = u; }
                            }
                        }
                        ++srcCnt;
                    }
                }

                nxt.clear();
                for (int qi : rem) {
                    if (col < qlo[qi] || col > qhi[qi]) { nxt.push_back(qi); continue; }
                    const int s = sid(qr1[qi], qc1[qi], 0);
                    const int re = qr2[qi], ce = qc2[qi];
                    int tRaw[2], tn = 0;
                    if (g[re][ce] != 'R') tRaw[tn++] = sid(re, ce, 0);
                    if (g[re][ce] != 'B') tRaw[tn++] = sid(re, ce, 1);
                    long long best = -1;
                    for (int k = 0; k < srcCnt; ++k) {
                        const int* d = dptr + (size_t)k * V;
                        if (d[s] < 0) continue;
                        for (int j = 0; j < tn; ++j) {
                            if (d[tRaw[j]] < 0) continue;
                            const long long c2 = (long long)d[s] + d[tRaw[j]];
                            if (best < 0 || c2 < best) best = c2;
                        }
                    }
                    ansFlag[qi] = (best >= 0 && best <= qK[qi]) ? 1 : 0;
                    settled[qi] = 1;
                }
                rem.swap(nxt);
                stepsLeft -= colCost;
            }
        }

        // ---------------- 兜底：单点 BFS（按 K 截断） ----------------
        dist1.assign(V, 0);
        stamp.assign(V, 0);
        int curStamp = 0;
        for (int qi = 0; qi < Q; ++qi) {
            if (settled[qi]) continue;
            const int rs = qr1[qi], cs = qc1[qi];
            const int K = (int)min<long long>(qK[qi], V);
            const int s = sid(rs, cs, 0);
            const int tcell = qr2[qi] * M + qc2[qi];

            ++curStamp;
            int head = 0, tail = 0;
            stamp[s] = curStamp;
            dist1[s] = 0;
            que[tail++] = s;
            char got = 0;
            while (head < tail) {
                const int v = que[head++];
                const int dv = dist1[v];
                if ((v >> 1) == tcell) { got = 1; break; }
                if (dv == K) continue;
                for (int e = adjStart[v]; e < adjStart[v + 1]; ++e) {
                    const int u = adj[e];
                    if (stamp[u] == curStamp) continue;
                    stamp[u] = curStamp;
                    dist1[u] = dv + 1;
                    que[tail++] = u;
                }
            }
            ansFlag[qi] = got;
        }

        for (int i = 0; i < Q; ++i) out += ansFlag[i] ? "YES\n" : "NO\n";
    }
    cout << out << endl;
    return 0;
}
