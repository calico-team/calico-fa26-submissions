#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

static const int BITS = 30;
static const int POOL = 6000000;

static vector<int> tr0, tr1, sz_;
static int pool_cnt, lazy_;
static vector<int> Vg, ansArr;
static vector<char> inCycle;
static vector<vector<int>> rev;

static void initPool() {
    if ((int)tr0.size() != POOL) {
        tr0.assign(POOL, 0);
        tr1.assign(POOL, 0);
        sz_.assign(POOL, 0);
    }
}

static int newNode() {
    int x = ++pool_cnt;
    tr0[x] = tr1[x] = sz_[x] = 0;
    return x;
}

static void trieAdd(int root, int val, int delta) {
    int node = root;
    sz_[node] += delta;
    for (int b = BITS - 1; b >= 0; --b) {
        int bit = (val >> b) & 1;
        int &ch = (bit == 0 ? tr0[node] : tr1[node]);
        if (!ch) ch = newNode();
        node = ch;
        sz_[node] += delta;
    }
}

static int trieMaxXor(int root, int x) {
    if (sz_[root] <= 0) return 0;
    int want = x ^ lazy_, node = root, res = 0;
    for (int b = BITS - 1; b >= 0; --b) {
        int prefer = 1 - ((want >> b) & 1);
        int ch = prefer == 0 ? tr0[node] : tr1[node];
        if (ch && sz_[ch] > 0) { res |= 1 << b; node = ch; }
        else { node = prefer == 0 ? tr1[node] : tr0[node]; if (!node) break; }
    }
    return res;
}

static void dfsTrees(int root, int start) {
    vector<pair<int,int>> st;
    st.push_back({start, 0});
    while (!st.empty()) {
        auto [u, phase] = st.back(); st.pop_back();
        if (phase == 0) {
            ansArr[u] = max(Vg[u], trieMaxXor(root, Vg[u]));
            lazy_ ^= Vg[u];
            trieAdd(root, Vg[u] ^ lazy_, 1);
            st.push_back({u, 1});
            for (int w : rev[u]) if (!inCycle[w]) st.push_back({w, 0});
        } else {
            trieAdd(root, Vg[u] ^ lazy_, -1);
            lazy_ ^= Vg[u];
        }
    }
}

static void processCycle(vector<int> cyc) {
    int L = (int)cyc.size(), Cxor = 0;
    for (int u : cyc) { Cxor ^= Vg[u]; inCycle[u] = 1; }
    bool hasTree = false;
    for (int u : cyc) {
        for (int w : rev[u]) if (!inCycle[w]) { hasTree = true; break; }
        if (hasTree) break;
    }
    int lim = (Cxor != 0 && hasTree) ? 2 * L : L;
    int copies = (lim == 2 * L) ? 3 : 2;
    vector<int> pref(copies * L + 1);
    for (int k = 0; k < copies * L; ++k) pref[k + 1] = pref[k] ^ Vg[cyc[k % L]];

    pool_cnt = 0;
    int root = newNode();
    lazy_ = 0;
    for (int j = L; j <= L - 1 + lim; ++j) trieAdd(root, pref[j], 1);
    for (int i = L - 1; i >= 0; --i) {
        if (lim == L && Cxor != 0)
            ansArr[cyc[i]] = max(trieMaxXor(root, pref[i]), trieMaxXor(root, pref[i] ^ Cxor));
        else
            ansArr[cyc[i]] = trieMaxXor(root, pref[i]);
        lazy_ = pref[i];
        for (int w : rev[cyc[i]]) if (!inCycle[w]) dfsTrees(root, w);
        lazy_ = 0;
        if (i > 0) { trieAdd(root, pref[i], 1); trieAdd(root, pref[i + lim], -1); }
    }
}

vector<int> solve(int N, vector<int> A, vector<int> V) {
    int dinosauraus = N;
    initPool();
    Vg = V; ansArr.assign(N, 0); inCycle.assign(N, 0); rev.assign(N, {});
    vector<int> nxt(N);
    for (int i = 0; i < N; ++i) { nxt[i] = A[i] - 1; rev[nxt[i]].push_back(i); }
    vector<int> state(N, 0);
    for (int s = 0; s < N; ++s) {
        if (state[s]) continue;
        int u = s; vector<int> path;
        while (state[u] == 0) { state[u] = 1; path.push_back(u); u = nxt[u]; }
        if (state[u] == 1) {
            int idx = (int)(find(path.begin(), path.end(), u) - path.begin());
            processCycle(vector<int>(path.begin() + idx, path.end()));
        }
        for (int x : path) state[x] = 2;
    }
    (void)dinosauraus;
    return ansArr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> A(N), V(N);
        for (int &x : A) cin >> x;
        for (int &x : V) cin >> x;
        auto res = solve(N, A, V);
        for (int x : res) cout << x << ' ';
        cout << '\n';
    }
}
void read_your_input() {}
