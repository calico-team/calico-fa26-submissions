#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<class T> using V = vector<T>;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define pb push_back
#define eb emplace_back

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

struct XorTrie {
    static constexpr int B = 30;
    struct Node {
        int nxt[2]{0, 0};
        int cnt = 0;
    };
    V<Node> t;

    XorTrie(int reserve_elements = 0) {
        init(reserve_elements);
    }

    void init(int reserve_elements = 0) {
        t.clear();
        if (reserve_elements > 0) t.reserve(reserve_elements * B + 2);
        t.eb(); // root = 0
    }

    void reset() {
        t.clear();
        t.eb();
    }

    void update(int x, int delta) {
        int u = 0;
        t[u].cnt += delta;
        for (int b = B - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!t[u].nxt[bit]) {
                t[u].nxt[bit] = sz(t);
                t.eb();
            }
            u = t[u].nxt[bit];
            t[u].cnt += delta;
        }
    }

    int queryMax(int x) const {
        int u = 0, ans = 0;
        for (int b = B - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            int c_want = t[u].nxt[want];
            if (c_want && t[c_want].cnt > 0) {
                ans |= (1 << b);
                u = c_want;
            } else {
                u = t[u].nxt[bit];
            }
        }
        return ans;
    }
};

void solve() {
    int N;
    cin >> N;
    V<int> A(N), val(N);
    V<V<int>> radj(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        --A[i];
        radj[A[i]].pb(i);
    }
    for (int i = 0; i < N; i++) {
        cin >> val[i];
    }

    V<int> state(N, 0); // 0 = unvisited, 1 = visiting, 2 = done
    V<uint8_t> on_cycle(N, 0);
    V<int> pot(N, 0), ans(N, 0);

    XorTrie trie(2 * N);

    for (int i = 0; i < N; i++) {
        if (state[i] != 0) continue;

        int u = i;
        while (state[u] == 0) {
            state[u] = 1;
            u = A[u];
        }

        // Since we process an entire weakly connected component once we find its cycle,
        // state[u] is guaranteed to be 1 here.
        V<int> cyc;
        int cur = u;
        do {
            cyc.pb(cur);
            on_cycle[cur] = 1;
            cur = A[cur];
        } while (cur != u);

        int L = sz(cyc);
        V<int> P(2 * L + 1, 0);
        for (int j = 0; j < 2 * L; j++) {
            P[j + 1] = P[j] ^ val[cyc[j % L]];
        }

        trie.reset();
        for (int j = 0; j < 2 * L; j++) {
            trie.update(P[j], +1);
        }

        auto dfs = [&](auto&& self, int x) -> void {
            state[x] = 2;
            ans[x] = trie.queryMax(pot[x]);
            trie.update(pot[x], +1);
            for (int y : radj[x]) {
                if (on_cycle[y]) continue;
                pot[y] = pot[x] ^ val[y];
                self(self, y);
            }
            trie.update(pot[x], -1);
        };

        for (int j = 0; j < L; j++) {
            pot[cyc[j]] = P[j];
        }
        for (int j = 0; j < L; j++) {
            dfs(dfs, cyc[j]);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << (i == N - 1 ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}
