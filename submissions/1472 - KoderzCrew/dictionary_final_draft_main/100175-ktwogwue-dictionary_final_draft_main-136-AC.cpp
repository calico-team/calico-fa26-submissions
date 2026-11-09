#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static int ch[6100000][2];
static int cnt[6100000];
static int tn;

static void tins(int x, int d) {
    int u = 0;
    for (int b = 29; b >= 0; b--) {
        int c = (x >> b) & 1;
        if (!ch[u][c]) ch[u][c] = ++tn;
        u = ch[u][c];
        cnt[u] += d;
    }
}
static int tq(int x) {
    int u = 0, r = 0;
    for (int b = 29; b >= 0; b--) {
        int c = ((x >> b) & 1) ^ 1;
        int v = ch[u][c];
        if (v && cnt[v] > 0) { r |= 1 << b; u = v; }
        else u = ch[u][c ^ 1];
    }
    return r;
}
static int sq(const vector<int>& S, int y) {
    int lo = 0, hi = S.size(), r = 0;
    for (int b = 29; b >= 0; b--) {
        int pm = ((1 << 30) - 1) ^ ((1 << b) - 1) ^ (1 << b); // unused
        (void)pm;
        int base = (lo < hi) ? (S[lo] >> (b + 1)) << (b + 1) : 0;
        int mid = lower_bound(S.begin() + lo, S.begin() + hi, base | (1 << b)) - S.begin();
        int want = ((y >> b) & 1) ^ 1;
        if (want) { if (mid < hi) { lo = mid; r |= 1 << b; } else hi = mid; }
        else { if (lo < mid) { hi = mid; r |= 1 << b; } else lo = mid; }
    }
    return r;
}

vector<int> solve(int N, vector<int> A, vector<int> V) {
    for (int& a : A) a--;
    vector<int> st(N, 0), ans(N, 0), pre(N, 0), cid(N, -1);
    vector<char> onc(N, 0);
    // find cycles
    vector<vector<int>> cycles;
    for (int i = 0; i < N; i++) if (!st[i]) {
        int u = i;
        while (!st[u]) { st[u] = i + 1; u = A[u]; }
        if (st[u] == i + 1) {
            vector<int> cy; int v = u;
            do { cy.push_back(v); onc[v] = 1; v = A[v]; } while (v != u);
            cycles.push_back(cy);
        }
        u = i;
        while (st[u] == i + 1) { st[u] = -1; u = A[u]; }
    }
    vector<vector<int>> rev(N);
    for (int i = 0; i < N; i++) if (!onc[i]) rev[A[i]].push_back(i);
    vector<int> Q(N, 0);
    for (auto& cy : cycles) {
        int m = cy.size();
        vector<int> p(m + 1, 0);
        for (int k = 0; k < m; k++) p[k + 1] = p[k] ^ V[cy[k]];
        int C = p[m];
        vector<int> U;
        for (int k = 0; k < m; k++) { U.push_back(p[k]); U.push_back(p[k] ^ C); }
        sort(U.begin(), U.end());
        U.erase(unique(U.begin(), U.end()), U.end());
        for (int k = 0; k < m; k++) {
            int c = cy[k];
            ans[c] = sq(U, p[k]);
            // DFS tail
            tn = 0; ch[0][0] = ch[0][1] = 0;
            tins(0, 1);
            vector<pair<int,int>> stk; // node, state
            for (int v : rev[c]) stk.push_back({v, 0});
            // iterative
            vector<int> stack2;
            stk.clear();
            stk.push_back({c, -1});
            while (!stk.empty()) {
                auto [u, it] = stk.back();
                if (it == -1) {
                    stk.back().second = 0;
                    if (u != c) {
                        Q[u] = V[u] ^ Q[A[u]];
                        tins(Q[u], 1);
                        ans[u] = max(tq(Q[u]), sq(U, Q[u] ^ p[k]));
                    } else Q[u] = 0;
                    continue;
                }
                if (it < (int)rev[u].size()) {
                    stk.back().second++;
                    stk.push_back({rev[u][it], -1});
                } else {
                    if (u != c) tins(Q[u], -1);
                    stk.pop_back();
                }
            }
            // reset trie nodes lazily: clear used nodes
            for (int i = 0; i <= tn; i++) { ch[i][0] = ch[i][1] = 0; cnt[i] = 0; }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> A(N), V(N);
        for (int& i : A) cin >> i;
        for (int& i : V) cin >> i;
        vector<int> ans = solve(N, A, V);
        for (int& i : ans) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
