#include <bits/stdc++.h>
using namespace std;

static const int INF = 1000000000;

struct Query {
    int sr, sc, er, ec;
    long long K;
};

static int N, M;
static vector<string> grid;
static vector<Query> qs;
static vector<long long> best;

static char* ibuf;
static size_t ipos = 0, ilen = 0;

static inline int readInt() {
    while (ipos < ilen && (ibuf[ipos] < '0' || ibuf[ipos] > '9')) ipos++;
    int x = 0;
    while (ipos < ilen && ibuf[ipos] >= '0' && ibuf[ipos] <= '9') { x = x * 10 + (ibuf[ipos] - '0'); ipos++; }
    return x;
}

static string readToken() {
    while (ipos < ilen && (ibuf[ipos] == ' ' || ibuf[ipos] == '\n' || ibuf[ipos] == '\r' || ibuf[ipos] == '\t')) ipos++;
    size_t st = ipos;
    while (ipos < ilen && !(ibuf[ipos] == ' ' || ibuf[ipos] == '\n' || ibuf[ipos] == '\r' || ibuf[ipos] == '\t')) ipos++;
    return string(ibuf + st, ibuf + ipos);
}

// State index inside the column range [l, r]:  (col - l) * 2N + row * 2 + mode   (mode 0 = blue, 1 = red)
// Every step and every spin costs 1 and can be undone, so the graph is undirected.
static void solveRange(int l, int r, const vector<int>& ids) {
    if (ids.empty() || l > r) return;

    int mid = (l + r) / 2;
    int w = r - l + 1;
    int S = 2 * N * w;
    int SRC = 2 * N;                 // BFS sources: every (row, mode) in column mid

    vector<unsigned char> act(S), normalTile(S);
    for (int c = l; c <= r; c++) {
        for (int row = 0; row < N; row++) {
            char t = grid[row][c];
            int base = (c - l) * 2 * N + row * 2;
            act[base]     = (t != 'R');   // blue mode: '.' and 'B' are active
            act[base + 1] = (t != 'B');   // red mode:  '.' and 'R' are active
            normalTile[base] = normalTile[base + 1] = (t == '.');
        }
    }

    vector<int> dist((size_t)S * SRC, INF);   // dist[state * SRC + source]
    vector<int> tmp(S), queue(S);

    for (int src = 0; src < SRC; src++) {
        int row = src / 2, mode = src % 2;
        int s0 = (mid - l) * 2 * N + row * 2 + mode;
        if (!act[s0]) continue;
        fill(tmp.begin(), tmp.end(), INF);
        int head = 0, tail = 0;
        tmp[s0] = 0;
        queue[tail++] = s0;
        while (head < tail) {
            int cur = queue[head++];
            int d = tmp[cur] + 1;
            int rowc = (cur >> 1) % N;
            int nb;
            if (normalTile[cur]) {                       // spin
                nb = cur ^ 1;
                if (tmp[nb] == INF) { tmp[nb] = d; queue[tail++] = nb; }
            }
            if (rowc > 0) {                              // up
                nb = cur - 2;
                if (act[nb] && tmp[nb] == INF) { tmp[nb] = d; queue[tail++] = nb; }
            }
            if (rowc < N - 1) {                          // down
                nb = cur + 2;
                if (act[nb] && tmp[nb] == INF) { tmp[nb] = d; queue[tail++] = nb; }
            }
            if (cur - 2 * N >= 0) {                      // left
                nb = cur - 2 * N;
                if (act[nb] && tmp[nb] == INF) { tmp[nb] = d; queue[tail++] = nb; }
            }
            if (cur + 2 * N < S) {                       // right
                nb = cur + 2 * N;
                if (act[nb] && tmp[nb] == INF) { tmp[nb] = d; queue[tail++] = nb; }
            }
        }
        for (int i = 0; i < S; i++) dist[(size_t)i * SRC + src] = tmp[i];
    }

    // Any shortest path inside this range either touches column mid or stays strictly on one side.
    vector<int> leftIds, rightIds;
    for (int id : ids) {
        const Query& q = qs[id];
        size_t s0 = (size_t)((q.sc - l) * 2 * N + q.sr * 2) * SRC;     // start is always taken in blue mode
        size_t e0 = (size_t)((q.ec - l) * 2 * N + q.er * 2) * SRC;     // destination in blue mode
        size_t e1 = e0 + SRC;                                          // destination in red mode
        long long b = best[id];
        for (int j = 0; j < SRC; j++) {
            int ds = dist[s0 + j];
            if (ds >= INF) continue;
            int de = min(dist[e0 + j], dist[e1 + j]);
            if (de >= INF) continue;
            long long cand = (long long)ds + de;
            if (cand < b) b = cand;
        }
        best[id] = b;
        if (q.sc < mid && q.ec < mid) leftIds.push_back(id);
        else if (q.sc > mid && q.ec > mid) rightIds.push_back(id);
    }

    vector<int>().swap(dist);
    vector<int>().swap(tmp);
    vector<int>().swap(queue);
    vector<unsigned char>().swap(act);
    vector<unsigned char>().swap(normalTile);

    solveRange(l, mid - 1, leftIds);
    solveRange(mid + 1, r, rightIds);
}

int main() {
    {
        size_t cap = 1 << 22;
        ibuf = (char*)malloc(cap);
        size_t n;
        while ((n = fread(ibuf + ilen, 1, cap - ilen, stdin)) > 0) {
            ilen += n;
            if (ilen == cap) { cap *= 2; ibuf = (char*)realloc(ibuf, cap); }
        }
    }

    int T = readInt();
    string out;
    while (T--) {
        N = readInt(); M = readInt();
        int Q = readInt();
        grid.assign(N, string());
        for (int i = 0; i < N; i++) grid[i] = readToken();
        qs.resize(Q);
        for (int i = 0; i < Q; i++) {
            qs[i].sr = readInt(); qs[i].sc = readInt();
            qs[i].er = readInt(); qs[i].ec = readInt();
            qs[i].K = readInt();
        }
        best.assign(Q, LLONG_MAX);
        vector<int> all(Q);
        for (int i = 0; i < Q; i++) all[i] = i;
        solveRange(0, M - 1, all);
        for (int i = 0; i < Q; i++) out += (best[i] <= qs[i].K) ? "YES\n" : "NO\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
