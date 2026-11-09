#include <bits/stdc++.h>
using namespace std;
static char ibuf[1 << 22];
static int ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return (unsigned char)ibuf[ipos++];
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    if (c == -1) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}

static inline string readToken() {
    int c = gc();
    while (c != -1 && (c == ' ' || c == '\n' || c == '\r' || c == '\t')) c = gc();
    string s;
    while (c != -1 && c != ' ' && c != '\n' && c != '\r' && c != '\t') {
        s.push_back((char)c);
        c = gc();
    }
    return s;
}
struct DSU {
    vector<int> p, sz;

    void init(int n) {
        p.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};
int main() {
    int T = readInt();
    if (T <= 0) return 0;

    string out;
    out.reserve(1 << 16);

    vector<string> g;
    DSU dsu;

    while (T--) {
        int N = readInt(), M = readInt(), Q = readInt();
        if (N <= 0 || M <= 0) return 0;

        g.assign(N, string());
        for (int i = 0; i < N; ++i) g[i] = readToken();

        int cells = N * M;
        dsu.init(cells);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                char cur = g[r][c];
                if (c + 1 < M) {
                    char nb = g[r][c + 1];
                    bool ok = !((cur == 'R' && nb == 'B') || (cur == 'B' && nb == 'R'));
                    if (ok) dsu.unite(r * M + c, r * M + c + 1);
                }
                if (r + 1 < N) {
                    char nb = g[r + 1][c];
                    bool ok = !((cur == 'R' && nb == 'B') || (cur == 'B' && nb == 'R'));
                    if (ok) dsu.unite(r * M + c, (r + 1) * M + c);
                }
            }
        }

        for (int qi = 0; qi < Q; ++qi) {
            int rs = readInt(), cs = readInt(), re = readInt(), ce = readInt();
            bool ok = dsu.find(rs * M + cs) == dsu.find(re * M + ce);
            out += ok ? "YES\n" : "NO\n";
        }
    }
    return 0;
}
