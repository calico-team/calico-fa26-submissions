#ifndef SMALLK
#define SMALLK 8
#endif
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef vector<u64> BS;

struct Row { BS c; int rhs; int piv; };
static int W;

static inline bool tb(const BS &a, int i) { return (a[i >> 6] >> (i & 63)) & 1ULL; }
static int popc(const BS &a) { int s = 0; for (u64 x : a) s += __builtin_popcountll(x); return s; }
static bool anyb(const BS &a) { for (u64 x : a) if (x) return true; return false; }
static int lowbit(const BS &a) {
    for (int w = 0; w < (int)a.size(); w++) if (a[w]) return w * 64 + __builtin_ctzll(a[w]);
    return -1;
}

static vector<Row> addrow(const vector<Row> &rows, const BS &l, int rhs0) {
    int piv = lowbit(l);
    vector<Row> nr;
    nr.reserve(rows.size() + 1);
    for (const Row &r : rows) {
        Row q = r;
        if (tb(r.c, piv)) {
            for (int w = 0; w < W; w++) q.c[w] ^= l[w];
            q.rhs ^= rhs0;
        }
        nr.push_back(move(q));
    }
    nr.push_back(Row{l, rhs0, piv});
    return nr;
}

static void forcedSets(const vector<Row> &rows, BS &F0, BS &F1) {
    F0.assign(W, 0); F1.assign(W, 0);
    for (const Row &r : rows) {
        if (popc(r.c) == 1) {
            if (r.rhs) F1[r.piv >> 6] |= 1ULL << (r.piv & 63);
            else F0[r.piv >> 6] |= 1ULL << (r.piv & 63);
        }
    }
}

static bool pairOk(const vector<Row> &rows, const BS &C0, const BS &C1) {
    BS F0, F1;
    forcedSets(rows, F0, F1);
    BS U(W), t(W);
    int cf = 0;
    for (int w = 0; w < W; w++) {
        cf += __builtin_popcountll((C0[w] & F0[w]) | (C1[w] & F1[w]));
        U[w] = (C0[w] | C1[w]) & ~(F0[w] | F1[w]);
    }
    if (cf >= 2) return true;
    if (cf == 1) return anyb(U);
    if (popc(U) < 2) return false;
    BS pivmask(W, 0);
    for (const Row &r : rows) pivmask[r.piv >> 6] |= 1ULL << (r.piv & 63);
    BS Uf(W);
    for (int w = 0; w < W; w++) Uf[w] = U[w] & ~pivmask[w];
    if (popc(Uf) >= 2) return true;
    map<BS, vector<pair<int, int>>> classes;
    if (anyb(Uf)) classes[Uf].push_back({lowbit(Uf), 0});
    for (const Row &r : rows) {
        if (tb(U, r.piv)) {
            BS key = r.c;
            key[r.piv >> 6] ^= 1ULL << (r.piv & 63);
            classes[key].push_back({r.piv, r.rhs});
        }
    }
    if (classes.size() >= 2) return true;
    for (auto &kv : classes) {
        for (int tau = 0; tau < 2; tau++) {
            int cnt = 0;
            for (auto &pr : kv.second) {
                int v = pr.second ^ tau;
                if ((v == 0 && tb(C0, pr.first)) || (v == 1 && tb(C1, pr.first))) cnt++;
            }
            if (cnt >= 2) return true;
        }
    }
    return false;
}

static int solveSmall(int X0, const vector<int> &EL, const vector<int> &ER) {
    int K = EL.size();
    int dl[16], c0[16], c1[16];
    for (int i = 0; i < K; i++) {
        int x = EL[i] ^ ER[i];
        int d = 31 - __builtin_clz(x);
        int low = (1 << d) - 1;
        dl[i] = x; c0[i] = (~EL[i]) & low; c1[i] = ER[i] & low;
    }
    int best = 0;
    for (int mask = 0; mask < (1 << K); mask++) {
        int X = X0, cap = 0, cap2 = 0;
        for (int i = 0; i < K; i++) {
            int c;
            if ((mask >> i) & 1) { X ^= dl[i]; c = c1[i]; } else c = c0[i];
            cap2 |= cap & c;
            cap |= c;
        }
        int v = (cap & ~X) | (cap2 & X);
        if (v) X |= (1 << (32 - __builtin_clz(v))) - 1;
        best = max(best, X);
    }
    return best;
}

static int solveGeneral(int X0, const vector<int> &EL, const vector<int> &ER) {
    int K = EL.size();
    int D = 0;
    for (int i = 0; i < K; i++) D = max(D, 31 - __builtin_clz(EL[i] ^ ER[i]));
    W = (K + 63) / 64;
    int w30 = D + 1;
    vector<BS> Lb(w30, BS(W, 0)), Rb(w30, BS(W, 0)), Db(w30, BS(W, 0)), GT(w30, BS(W, 0));
    for (int e = 0; e < K; e++)
        for (int b = 0; b <= D; b++) {
            if ((EL[e] >> b) & 1) Lb[b][e >> 6] |= 1ULL << (e & 63);
            if ((ER[e] >> b) & 1) Rb[b][e >> 6] |= 1ULL << (e & 63);
        }
    BS acc(W, 0);
    for (int b = D; b >= 0; b--) {
        for (int w = 0; w < W; w++) Db[b][w] = Lb[b][w] ^ Rb[b][w];
        GT[b] = acc;
        for (int w = 0; w < W; w++) acc[w] |= Db[b][w];
    }
    int P = (D + 1 >= 31) ? 0 : ((X0 >> (D + 1)) << (D + 1));
    vector<Row> rows;
    BS C0(W), C1(W), cand(W);
    for (int b = D; b >= 0; b--) {
        BS l = Db[b];
        int c = (X0 >> b) & 1;
        for (const Row &r : rows)
            if (tb(l, r.piv)) {
                for (int w = 0; w < W; w++) l[w] ^= r.c[w];
                c ^= r.rhs;
            }
        bool hasL = anyb(l);
        const BS &g = GT[b];
        if (anyb(g)) {
            for (int w = 0; w < W; w++) {
                C0[w] = g[w] & ~Lb[b][w];
                C1[w] = g[w] & Rb[b][w];
                cand[w] = C0[w] | C1[w];
            }
            if (anyb(cand)) {
                int nr = rows.size() + (hasL ? 1 : 0);
                int pc = popc(cand);
                int full = (1 << (b + 1)) - 1;
                if (hasL || !c) {
                    bool capable = false;
                    if (pc > nr) capable = true;
                    else {
                        vector<Row> r2 = hasL ? addrow(rows, l, c) : rows;
                        BS F0, F1;
                        forcedSets(r2, F0, F1);
                        for (int w = 0; w < W; w++)
                            if ((C0[w] & ~F1[w]) || (C1[w] & ~F0[w])) { capable = true; break; }
                    }
                    if (capable) return P | full;
                }
                if (hasL || c) {
                    if (pc >= nr + 2) return P | full;
                    vector<Row> r2 = hasL ? addrow(rows, l, c ^ 1) : rows;
                    if (pairOk(r2, C0, C1)) return P | full;
                }
            }
        }
        if (hasL) {
            rows = addrow(rows, l, c ^ 1);
            P |= 1 << b;
        } else {
            P |= c << b;
        }
    }
    return P;
}

static char buf[1 << 25];
int main() {
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    buf[len] = 0;
    char *p = buf;
    auto readInt = [&]() -> int {
        while (*p && (*p < '0' || *p > '9')) p++;
        int x = 0;
        while (*p >= '0' && *p <= '9') x = x * 10 + (*p++ - '0');
        return x;
    };
    int T = readInt();
    string out;
    vector<int> L, R, EL, ER;
    while (T--) {
        int N = readInt();
        L.assign(N, 0); R.assign(N, 0);
        for (int i = 0; i < N; i++) L[i] = readInt();
        for (int i = 0; i < N; i++) R[i] = readInt();
        int X0 = 0;
        EL.clear(); ER.clear();
        for (int i = 0; i < N; i++) {
            X0 ^= L[i];
            if (L[i] != R[i]) { EL.push_back(L[i]); ER.push_back(R[i]); }
        }
        int ans;
        if (EL.empty()) ans = X0;
        else if ((int)EL.size() <= SMALLK) ans = solveSmall(X0, EL, ER);
        else ans = solveGeneral(X0, EL, ER);
        out += to_string(ans);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
    return 0;
}