#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int ch[2];
        int cnt;
        Node() { ch[0] = ch[1] = -1; cnt = 0; }
    };
    vector<Node> t;
    Trie() { t.emplace_back(); }
    void clear() { t.clear(); t.emplace_back(); }
    void add(int x, int delta) {
        int v = 0;
        t[v].cnt += delta;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            if (t[v].ch[bit] == -1) {
                t[v].ch[bit] = (int)t.size();
                t.emplace_back();
            }
            v = t[v].ch[bit];
            t[v].cnt += delta;
        }
    }
    void insert(int x) { add(x, 1); }
    void erase(int x) { add(x, -1); }
    int max_xor(int x) const {
        int v = 0, res = 0;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            int nxt = t[v].ch[want];
            if (nxt != -1 && t[nxt].cnt > 0) {
                res |= (1 << b);
                v = nxt;
            } else {
                v = t[v].ch[bit];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N + 1);
        for (int i = 1; i <= N; i++) cin >> A[i];

        vector<int> V(N + 1);
        for (int i = 1; i <= N; i++) cin >> V[i];

        vector<vector<int>> rev(N + 1);
        vector<int> indeg(N + 1, 0);

        for (int i = 1; i <= N; i++) {
            rev[A[i]].push_back(i);
            indeg[A[i]]++;
        }

        queue<int> q;
        vector<int> isCycle(N + 1, 1);

        for (int i = 1; i <= N; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            isCycle[u] = 0;
            int v = A[u];

            if (--indeg[v] == 0) q.push(v);
        }

        vector<int> ans(N + 1, 0);
        vector<int> visCycle(N + 1, 0);

        for (int start = 1; start <= N; start++) {
            if (!isCycle[start] || visCycle[start]) continue;

            // Collect the cycle.
            vector<int> cyc;
            int cur = start;

            while (!visCycle[cur]) {
                visCycle[cur] = 1;
                cyc.push_back(cur);
                cur = A[cur];
            }

            int L = (int)cyc.size();

            vector<int> P(2 * L + 1, 0);
            for (int k = 0; k < 2 * L; k++) {
                P[k + 1] = P[k] ^ V[cyc[k % L]];
            }

            int Xc = P[L];

            Trie cycleTrie;
            for (int k = 1; k <= L; k++) {
                cycleTrie.insert(P[k]);
            }

            struct Item {
                int u;
                int cum;
                int stage;
            };

            Trie pathTrie;

            for (int j = 0; j < L; j++) {
                int cnode = cyc[j];
                int Pj = P[j];

                int best = max(
                    cycleTrie.max_xor(Pj),
                    cycleTrie.max_xor(Pj ^ Xc)
                );

                ans[cnode] = best;

                // DFS over the in-tree rooted at this cycle node.
                pathTrie.clear();
                pathTrie.insert(0);

                vector<Item> st;

                for (int ch : rev[cnode]) {
                    if (!isCycle[ch]) {
                        st.push_back({ch, V[ch], 0});
                    }
                }

                while (!st.empty()) {
                    Item it = st.back();
                    st.pop_back();

                    int u = it.u;
                    int cum = it.cum;

                    if (it.stage == 1) {
                        pathTrie.erase(cum);
                        continue;
                    }

                    int treeBest = pathTrie.max_xor(cum);
                    int cycBest1 = cycleTrie.max_xor(cum ^ Pj);
                    int cycBest2 = cycleTrie.max_xor(cum ^ Pj ^ Xc);

                    ans[u] = max({treeBest, cycBest1, cycBest2});

                    st.push_back({u, cum, 1});
                    pathTrie.insert(cum);

                    for (int ch : rev[u]) {
                        if (!isCycle[ch]) {
                            st.push_back({ch, cum ^ V[ch], 0});
                        }
                    }
                }

                // Slide the cycle window.
                if (j + 1 < L) {
                    cycleTrie.erase(P[j + 1]);
                    cycleTrie.insert(P[j + L + 1]);
                }
            }
        }

        for (int i = 1; i <= N; i++) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
