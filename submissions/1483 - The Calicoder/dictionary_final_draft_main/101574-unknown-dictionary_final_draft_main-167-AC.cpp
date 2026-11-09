
#include <bits/stdc++.h>
using namespace std;

const int BITS = 29;

struct Trie {
    struct Node {
        int ch[2] = {-1, -1};
        int cnt = 0;
    };

    vector<Node> tr;

    Trie() {
        tr.emplace_back();
    }

    void insert(int x) {
        int u = 0;
        tr[u].cnt++;

        for (int b = BITS; b >= 0; b--) {
            int bit = (x >> b) & 1;

            if (tr[u].ch[bit] == -1) {
                tr[u].ch[bit] = tr.size();
                tr.emplace_back();
            }

            u = tr[u].ch[bit];
            tr[u].cnt++;
        }
    }

    void erase(int x) {
        int u = 0;
        tr[u].cnt--;

        for (int b = BITS; b >= 0; b--) {
            int bit = (x >> b) & 1;
            u = tr[u].ch[bit];
            tr[u].cnt--;
        }
    }

    int query(int x) {
        int u = 0, ans = 0;

        for (int b = BITS; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;

            int v = tr[u].ch[want];

            if (v != -1 && tr[v].cnt > 0) {
                ans |= (1 << b);
                u = v;
            } else {
                u = tr[u].ch[bit];
            }
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N + 1), V(N + 1);
        vector<int> indeg(N + 1, 0);
        vector<vector<int>> rev(N + 1);

        for (int i = 1; i <= N; i++) {
            cin >> A[i];
            indeg[A[i]]++;
            rev[A[i]].push_back(i);
        }

        for (int i = 1; i <= N; i++)
            cin >> V[i];

        queue<int> q;
        vector<bool> inCycle(N + 1, true);

        for (int i = 1; i <= N; i++) {
            if (indeg[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            inCycle[u] = false;

            int v = A[u];

            if (--indeg[v] == 0)
                q.push(v);
        }

        vector<int> ans(N + 1);
        vector<bool> seen(N + 1, false);

        for (int i = 1; i <= N; i++) {
            if (!inCycle[i] || seen[i])
                continue;

            vector<int> cycle;
            int u = i;

            do {
                seen[u] = true;
                cycle.push_back(u);
                u = A[u];
            } while (u != i);

            int L = cycle.size();

            vector<int> pref(L);
            int total = 0;

            for (int j = 0; j < L; j++) {
                pref[j] = total;
                total ^= V[cycle[j]];
            }

            Trie trie;

            for (int j = 0; j < L; j++) {
                trie.insert(pref[j]);
                trie.insert(pref[j] ^ total);
            }

            for (int j = 0; j < L; j++) {
                ans[cycle[j]] = trie.query(pref[j]);
            }

            for (int j = 0; j < L; j++) {
                int root = cycle[j];

                stack<tuple<int, int, bool>> st;

                for (int v : rev[root]) {
                    if (!inCycle[v]) {
                        st.push({v, pref[j] ^ V[v], false});
                    }
                }

                while (!st.empty()) {
                    auto [node, x, exiting] = st.top();
                    st.pop();

                    if (exiting) {
                        trie.erase(x);
                        continue;
                    }

                    trie.insert(x);
                    ans[node] = trie.query(x);

                    st.push({node, x, true});

                    for (int v : rev[node]) {
                        if (!inCycle[v]) {
                            st.push({
                                v,
                                x ^ V[v],
                                false
                            });
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= N; i++) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }

        cout << '\n';
    }
}
