#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int BITS = 30;
const int POOL = 30 * 200002 + 5;

struct Trie {
    int ch[POOL][2];
    int cnt[POOL];
    int sz;

    void reset() {
        sz = 1;
        ch[0][0] = ch[0][1] = 0;
        cnt[0] = 0;
    }

    void add(int x, int d) {
        int u = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int c = (x >> b) & 1;
            if (!ch[u][c]) {
                ch[sz][0] = ch[sz][1] = 0;
                cnt[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
            cnt[u] += d;
        }
    }

    int best(int x) {
        int u = 0, r = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int c = ((x >> b) & 1) ^ 1;
            int v = ch[u][c];
            if (v && cnt[v] > 0) {
                r |= 1 << b;
                u = v;
            } else {
                u = ch[u][c ^ 1];
            }
        }
        return r;
    }
};

static Trie cycT, anc;

vector<int> solve(int N, vector<int> A, vector<int> V) {
    vector<int> nxt(N), indeg(N, 0);
    for (int i = 0; i < N; i++) {
        nxt[i] = A[i] - 1;
        indeg[nxt[i]]++;
    }
    vector<char> onCycle(N, 1);
    vector<int> q;
    for (int i = 0; i < N; i++)
        if (indeg[i] == 0) q.push_back(i);
    for (size_t h = 0; h < q.size(); h++) {
        int u = q[h];
        onCycle[u] = 0;
        if (--indeg[nxt[u]] == 0) q.push_back(nxt[u]);
    }

    vector<int> first(N, -1), sib(N, -1);
    for (int i = 0; i < N; i++) {
        if (onCycle[i]) continue;
        sib[i] = first[nxt[i]];
        first[nxt[i]] = i;
    }

    vector<int> ans(N), T(N, 0), it(first), stk;
    vector<char> seen(N, 0);

    for (int s = 0; s < N; s++) {
        if (!onCycle[s] || seen[s]) continue;
        vector<int> cyc;
        int u = s;
        do {
            seen[u] = 1;
            cyc.push_back(u);
            u = nxt[u];
        } while (u != s);

        int L = cyc.size();
        vector<int> R(L + 1, 0);
        for (int r = 0; r < L; r++) R[r + 1] = R[r] ^ V[cyc[r]];
        int C = R[L];

        cycT.reset();
        for (int r = 0; r < L; r++) cycT.add(R[r], 1);

        for (int r = 0; r < L; r++) {
            int c = cyc[r];
            ans[c] = max(cycT.best(R[r]), cycT.best(R[r] ^ C));
            if (first[c] == -1) continue;

            anc.reset();
            anc.add(0, 1);
            T[c] = 0;
            stk.assign(1, c);
            while (!stk.empty()) {
                int x = stk.back();
                if (it[x] != -1) {
                    int i = it[x];
                    it[x] = sib[i];
                    T[i] = V[i] ^ T[x];
                    int e = T[i] ^ R[r];
                    ans[i] = max(anc.best(T[i]), max(cycT.best(e), cycT.best(e ^ C)));
                    anc.add(T[i], 1);
                    stk.push_back(i);
                } else {
                    if (x != c) anc.add(T[x], -1);
                    stk.pop_back();
                }
            }
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
