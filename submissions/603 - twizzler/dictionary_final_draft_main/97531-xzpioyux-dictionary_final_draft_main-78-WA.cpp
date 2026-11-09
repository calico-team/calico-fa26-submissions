#include <bits/stdc++.h>
using namespace std;

const int B = 29;

struct Trie {
    struct Node {
        int ch[2] = {0, 0};
        int cnt = 0;
    };

    vector<Node> t;

    Trie() {
        t.reserve(20000000);
        t.push_back(Node());
    }

    int insert(int prev, int x) {
        int cur = (int)t.size();
        t.push_back(t[prev]);
        t[cur].cnt++;

        int u = cur, v = prev;

        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int old = t[v].ch[bit];

            int nw = (int)t.size();
            t.push_back(t[old]);
            t[nw].cnt++;

            t[u].ch[bit] = nw;

            u = nw;
            v = old;
        }

        return cur;
    }

    int query(int r, int l, int x) {
        int ans = 0;
        int u = r, v = l;

        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;

            int a = t[t[u].ch[want]].cnt
                  - t[t[v].ch[want]].cnt;

            if (a > 0) {
                ans |= (1 << b);
                u = t[u].ch[want];
                v = t[v].ch[want];
            } else {
                u = t[u].ch[bit];
                v = t[v].ch[bit];
            }
        }

        return ans;
    }

    int query(int root, int x) {
        return query(root, 0, x);
    }
};

struct Cycle {
    vector<int> nodes;
    vector<int> roots;
    vector<int> pref;
    int xr = 0;
};

void read_your_input() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N), V(N);

        for (int &x : A) {
            cin >> x;
            --x;
        }

        for (int &x : V) cin >> x;

        vector<vector<int>> rev(N);
        vector<int> indeg(N, 0);

        for (int i = 0; i < N; i++) {
            rev[A[i]].push_back(i);
            indeg[A[i]]++;
        }

        queue<int> q;

        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (--indeg[A[u]] == 0) {
                q.push(A[u]);
            }
        }

        vector<int> inCycle(N, 0);

        for (int i = 0; i < N; i++) {
            if (indeg[i] > 0) inCycle[i] = 1;
        }

        Trie trie;

        vector<int> P(N, 0);
        vector<int> ver(N, 0);
        vector<int> parent(N, -1);
        vector<int> cycleId(N, -1);
        vector<int> cyclePos(N, -1);

        vector<Cycle> cycles;
        vector<int> visited(N, 0);

        for (int i = 0; i < N; i++) {
            if (!inCycle[i] || visited[i]) continue;

            Cycle cy;

            int u = i;

            while (!visited[u]) {
                visited[u] = 1;
                cy.nodes.push_back(u);
                u = A[u];
            }

            int id = (int)cycles.size();
            int L = (int)cy.nodes.size();

            for (int k = 0; k < L; k++) {
                int r = cy.nodes[k];

                cycleId[r] = id;
                cyclePos[r] = k;

                P[r] = V[r];
                ver[r] = trie.insert(0, P[r]);

                cy.xr ^= V[r];
            }

            if (L > 1) {
                vector<int> S(2 * L + 1, 0);

                for (int j = 1; j <= 2 * L; j++) {
                    S[j] = S[j - 1] ^ V[cy.nodes[(j - 1) % L]];
                }

                cy.pref = S;
                cy.roots.resize(2 * L + 1);

                cy.roots[0] = 0;

                for (int j = 1; j <= 2 * L; j++) {
                    cy.roots[j] =
                        trie.insert(cy.roots[j - 1], S[j]);
                }
            }

            vector<int> st;

            for (int r : cy.nodes) st.push_back(r);

            while (!st.empty()) {
                int x = st.back();
                st.pop_back();

                for (int v : rev[x]) {
                    if (inCycle[v]) continue;

                    parent[v] = x;
                    P[v] = P[x] ^ V[v];

                    cycleId[v] = id;
                    cyclePos[v] = cyclePos[x];

                    ver[v] = trie.insert(ver[x], P[v]);

                    st.push_back(v);
                }
            }

            cycles.push_back(move(cy));
        }

        vector<int> ans(N);

        for (int i = 0; i < N; i++) {
            int id = cycleId[i];
            int k = cyclePos[i];

            Cycle &cy = cycles[id];

            int L = (int)cy.nodes.size();

            if (L == 1) {
                ans[i] = max(P[i], P[i] ^ cy.xr);
                continue;
            }

            int l = k + 1;
            int r = k + L + 1;

            int target = P[i] ^ cy.pref[k + 1];

            int best = trie.query(
                cy.roots[r],
                cy.roots[l - 1],
                target
            );

            if (cy.xr != 0) {
                best = max(best, trie.query(
                    cy.roots[r],
                    cy.roots[l - 1],
                    target ^ cy.xr
                ));
            }

            if (parent[i] != -1) {
                best = max(
                    best,
                    trie.query(ver[parent[i]], P[i])
                );
            }

            ans[i] = best;
        }

        for (int i = 0; i < N; i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }

        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dinosauraus = 0;

    read_your_input();

    return 0;
}
