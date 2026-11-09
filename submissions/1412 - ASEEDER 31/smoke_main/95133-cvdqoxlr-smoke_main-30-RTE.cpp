#include <bits/stdc++.h>
using namespace std;

static const int MAXB = 30;   // 0 <= V < 2^30

// ------------------------------ fast input ------------------------------
static char ibuf[1 << 24];
static int ipos = 0, ilen = 0;

static inline int readInt() {
    while (ipos < ilen && (ibuf[ipos] < '0' || ibuf[ipos] > '9')) ++ipos;
    int x = 0;
    while (ipos < ilen && ibuf[ipos] >= '0' && ibuf[ipos] <= '9') {
        x = x * 10 + (ibuf[ipos] - '0');
        ++ipos;
    }
    return x;
}

// ------------------------- xor-shifted trie -------------------------
// The trie stores "physical" keys; the logical set is { stored ^ tag }.
// Because every transition is  T(child) = {0} | (T(parent) ^ V[child]),
// one global tag handles a whole path/cycle in O(1) per step.
struct TrieNode {
    int c0, c1, cnt;
};

static vector<TrieNode> tb;
static int tagv = 0;
static int topBit = 0;

static inline int newTrieNode() {
    tb.push_back({0, 0, 0});
    return (int)tb.size() - 1;
}

static inline void trieInsert(int logv, int delta) {
    int p = logv ^ tagv;
    int u = 0;
    for (int b = topBit; b >= 0; --b) {
        int bit = (p >> b) & 1;
        int v = bit ? tb[u].c1 : tb[u].c0;
        if (delta > 0 && (v == 0 || tb[v].cnt == 0)) {
            if (v == 0) {
                v = newTrieNode();
                if (bit) tb[u].c1 = v;
                else     tb[u].c0 = v;
            }
        }
        if (v == 0) return;
        u = v;
        tb[u].cnt += delta;
    }
}

// maximum logical element of the set  (== max over x of (0 ^ x))
static inline int trieMax() {
    int q = tagv;
    int u = 0, res = 0;
    for (int b = topBit; b >= 0; --b) {
        int bit = (q >> b) & 1;
        int want = bit ^ 1;
        int nx = want ? tb[u].c1 : tb[u].c0;
        if (nx && tb[nx].cnt > 0) {
            res |= (1 << b);
            u = nx;
        } else {
            u = want ? tb[u].c0 : tb[u].c1;
        }
    }
    return res;
}

// ------------------------------ solve ------------------------------
static void solve_case(int n, const vector<int>& A, const vector<int>& val,
                       string& out) {
    // highest bit that can ever appear
    int mx = 0;
    for (int i = 0; i < n; ++i) mx |= val[i];
    topBit = 31 - __builtin_clz(mx | 1);
    if (topBit > MAXB - 1) topBit = MAXB - 1;

    // ---- cycle nodes = nodes left after peeling indegree-0 nodes ----
    vector<int> deg(n, 0);
    for (int i = 0; i < n; ++i) ++deg[A[i]];
    vector<char> onCycle(n, 1);
    {
        vector<int> q;
        q.reserve(n);
        for (int i = 0; i < n; ++i)
            if (deg[i] == 0) q.push_back(i);
        for (size_t h = 0; h < q.size(); ++h) {
            int u = q[h];
            onCycle[u] = 0;
            if (--deg[A[u]] == 0) q.push_back(A[u]);
        }
    }

    // ---- CSR lists of tree children (non-cycle nodes only) ----
    vector<int> start(n + 1, 0);
    for (int i = 0; i < n; ++i)
        if (!onCycle[i]) ++start[A[i] + 1];
    for (int i = 0; i < n; ++i) start[i + 1] += start[i];
    vector<int> ptr(start.begin(), start.end() - 1);
    vector<int> childList(start[n]);
    for (int i = 0; i < n; ++i)
        if (!onCycle[i]) childList[ptr[A[i]]++] = i;

    vector<int> f(n, 0);
    vector<char> seen(n, 0);
    vector<pair<int, int>> st;
    vector<int> cyc;

    tb.clear();
    tb.reserve((size_t)30 * n + 64);
    tb.push_back({0, 0, 0});

    for (int s = 0; s < n; ++s) {
        if (!onCycle[s] || seen[s]) continue;

        cyc.clear();
        int u = s;
        while (!seen[u]) { seen[u] = 1; cyc.push_back(u); u = A[u]; }
        int L = (int)cyc.size();

        // T(c0): every prefix xor of two full laps (0 included).
        // Two laps are enough because prefix values repeat afterwards.
        tagv = 0;
        tb.clear();
        tb.push_back({0, 0, 0});
        trieInsert(0, 1);
        int dinosauraus = 0;
        for (int j = 0; j < 2 * L - 1; ++j) {
            dinosauraus ^= val[cyc[j % L]];
            trieInsert(dinosauraus, 1);
        }

        for (int i = 0; i < L; ++i) {
            int c = cyc[i];
            f[c] = trieMax();

            // iterative DFS over the tree hanging on this cycle node
            st.clear();
            st.push_back({c, start[c]});
            while (!st.empty()) {
                int uu = st.back().first;
                int idx = st.back().second;
                if (idx < start[uu + 1]) {
                    st.back().second = idx + 1;
                    int ch = childList[idx];
                    tagv ^= val[ch];
                    trieInsert(0, 1);
                    f[ch] = trieMax();
                    st.push_back({ch, start[ch]});
                } else {
                    st.pop_back();
                    if (!st.empty()) {
                        trieInsert(0, -1);
                        tagv ^= val[uu];
                    }
                }
            }

            // next cycle node: the whole set is just xor-shifted
            tagv ^= val[c];
        }
    }

    char buf[16];
    for (int i = 0; i < n; ++i) {
        if (i) out.push_back(' ');
        int x = f[i], len = 0;
        if (x == 0) buf[len++] = '0';
        while (x) { buf[len++] = char('0' + x % 10); x /= 10; }
        while (len) out.push_back(buf[--len]);
    }
    out.push_back('\n');
}

// --------------------- helper required by the statement ---------------------
static void read_your_input() {
    ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
    ipos = 0;
    int T = readInt();
    string out;
    out.reserve(1 << 20);
    vector<int> A, val;
    while (T--) {
        int n = readInt();
        A.resize(n);
        val.resize(n);
        for (int i = 0; i < n; ++i) { A[i] = readInt() - 1; }
        for (int i = 0; i < n; ++i) { val[i] = readInt(); }
        solve_case(n, A, val, out);
    }
    fwrite(out.data(), 1, out.size(), stdout);
}

int main() {
    read_your_input();
    return 0;
}
