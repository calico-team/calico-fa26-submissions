#include <bits/stdc++.h>
using namespace std;

static vector<int> c0, c1, cn;

static void resetTrie() {
    c0.assign(1, 0);
    c1.assign(1, 0);
    cn.assign(1, 0);
}

static void upd(int x, int d) {
    int u = 0;
    for (int b = 29; b >= 0; b--) {
        int bit = (x >> b) & 1;
        int nx = bit ? c1[u] : c0[u];
        if (!nx) {
            nx = (int)c0.size();
            c0.push_back(0);
            c1.push_back(0);
            cn.push_back(0);
            if (bit) c1[u] = nx; else c0[u] = nx;
        }
        u = nx;
        cn[u] += d;
    }
}

static int query(int x) {
    int u = 0, res = 0;
    for (int b = 29; b >= 0; b--) {
        int bit = (x >> b) & 1;
        int want = bit ^ 1;
        int nx = want ? c1[u] : c0[u];
        if (nx && cn[nx] > 0) {
            res |= (1 << b);
            u = nx;
        } else {
            u = bit ? c1[u] : c0[u];
        }
    }
    return res;
}

static char buf[1 << 25];
static size_t bl = 0, bp = 0;

static inline int gc() {
    if (bp == bl) {
        bl = fread(buf, 1, sizeof(buf), stdin);
        bp = 0;
        if (bl == 0) return -1;
    }
    return buf[bp++];
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    int T = readInt();
    string out;
    while (T--) {
        int n = readInt();
        vector<int> A(n), V(n);
        for (int i = 0; i < n; i++) A[i] = readInt() - 1;
        for (int i = 0; i < n; i++) V[i] = readInt();
        vector<int> indeg(n, 0);
        for (int i = 0; i < n; i++) indeg[A[i]]++;
        vector<char> removed(n, 0);
        vector<int> q;
        q.reserve(n);
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push_back(i);
        for (size_t h = 0; h < q.size(); h++) {
            int u = q[h];
            removed[u] = 1;
            if (--indeg[A[u]] == 0) q.push_back(A[u]);
        }
        vector<int> head(n, -1), nxt(n, -1);
        for (int v = 0; v < n; v++) {
            if (removed[v]) {
                nxt[v] = head[A[v]];
                head[A[v]] = v;
            }
        }
        vector<int> G(n, 0), ans(n, 0);
        vector<char> seen(n, 0);
        vector<int> cyc, Q, st;
        for (int s0 = 0; s0 < n; s0++) {
            if (removed[s0] || seen[s0]) continue;
            cyc.clear();
            Q.clear();
            int u = s0;
            int acc = 0;
            while (!seen[u]) {
                seen[u] = 1;
                cyc.push_back(u);
                Q.push_back(acc);
                acc ^= V[u];
                u = A[u];
            }
            int C = acc;
            int L = (int)cyc.size();
            resetTrie();
            for (int j = 0; j < L; j++) {
                upd(Q[j], 1);
                upd(Q[j] ^ C, 1);
            }
            for (int j = 0; j < L; j++) {
                int c = cyc[j];
                G[c] = Q[j];
                ans[c] = query(Q[j]);
            }
            vector<int> it = head;
            for (int j = 0; j < L; j++) {
                st.clear();
                st.push_back(cyc[j]);
                while (!st.empty()) {
                    int x = st.back();
                    if (it[x] != -1) {
                        int v = it[x];
                        it[x] = nxt[v];
                        G[v] = V[v] ^ G[x];
                        ans[v] = query(G[v]);
                        upd(G[v], 1);
                        st.push_back(v);
                    } else {
                        st.pop_back();
                        if (removed[x]) upd(G[x], -1);
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            out += to_string(ans[i]);
            out += (i + 1 < n ? ' ' : '\n');
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}