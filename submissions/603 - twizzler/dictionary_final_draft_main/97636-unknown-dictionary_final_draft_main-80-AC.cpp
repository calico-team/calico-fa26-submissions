#include <bits/stdc++.h>
using namespace std;

struct PersistentTrie {
    struct Node {
        int ch[2] = {0, 0};
        int cnt = 0;
    };

    vector<Node> tr;

    PersistentTrie(int reserve_nodes = 1) {
        tr.reserve(reserve_nodes);
        tr.push_back(Node());
    }

    int insert(int root, int x) {
        int nr = (int)tr.size();
        tr.push_back(tr[root]);
        tr[nr].cnt++;

        int u = nr, old = root;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int oldChild = tr[old].ch[bit];

            int newChild = (int)tr.size();
            tr.push_back(tr[oldChild]);
            tr[newChild].cnt++;

            tr[u].ch[bit] = newChild;
            u = newChild;
            old = oldChild;
        }
        return nr;
    }

    int maxXor(int rightRoot, int leftRoot, int x) const {
        int u = rightRoot, v = leftRoot;
        int ans = 0;

        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            int ru = tr[u].ch[want];
            int lv = tr[v].ch[want];

            if (tr[ru].cnt - tr[lv].cnt > 0) {
                ans |= (1 << b);
                u = ru;
                v = lv;
            } else {
                u = tr[u].ch[bit];
                v = tr[v].ch[bit];
            }
        }
        return ans;
    }
};

void read_your_input() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
        for (int i = 0; i < N; ++i) {
            rev[A[i]].push_back(i);
            ++indeg[A[i]];
        }

        queue<int> que;
        for (int i = 0; i < N; ++i)
            if (indeg[i] == 0) que.push(i);

        while (!que.empty()) {
            int u = que.front();
            que.pop();
            int v = A[u];
            if (--indeg[v] == 0) que.push(v);
        }

        vector<char> isCycle(N, false);
        for (int i = 0; i < N; ++i)
            if (indeg[i] > 0) isCycle[i] = true;

        // At most about 31 persistent nodes per inserted value.
        PersistentTrie trie(1 + (size_t)N * 65);

        vector<int> parent(N, -1), depthXor(N, 0);
        vector<int> treeRoot(N, 0);
        vector<int> cycleId(N, -1), cyclePos(N, -1);
        vector<char> seen(N, false);

        struct CycleInfo {
            vector<int> nodes;
            vector<int> pref;
            int leftRoot = 0, rightRoot = 0;
            int totalXor = 0;
        };
        vector<CycleInfo> cycles;

        for (int s = 0; s < N; ++s) {
            if (!isCycle[s] || seen[s]) continue;

            CycleInfo cy;
            int u = s;
            while (!seen[u]) {
                seen[u] = true;
                cy.nodes.push_back(u);
                u = A[u];
            }

            int L = (int)cy.nodes.size();
            cy.pref.assign(L + 1, 0);
            for (int j = 0; j < L; ++j) {
                cy.pref[j + 1] = cy.pref[j] ^ V[cy.nodes[j]];
            }
            cy.totalXor = cy.pref[L];

            cy.leftRoot = 0;
            int root = 0;
            for (int j = 1; j <= L; ++j) {
                root = trie.insert(root, cy.pref[j]);
            }
            for (int j = 1; j <= L; ++j) {
                root = trie.insert(root, cy.pref[j] ^ cy.totalXor);
            }
            cy.rightRoot = root;

            int id = (int)cycles.size();
            for (int j = 0; j < L; ++j) {
                int v = cy.nodes[j];
                cycleId[v] = id;
                cyclePos[v] = j;
                depthXor[v] = 0;
                treeRoot[v] = 0;
            }

            cycles.push_back(move(cy));
        }

        // Build incoming trees, starting from each cycle vertex.
        for (int id = 0; id < (int)cycles.size(); ++id) {
            vector<int> st = cycles[id].nodes;

            while (!st.empty()) {
                int u = st.back();
                st.pop_back();

                for (int v : rev[u]) {
                    if (isCycle[v]) continue;

                    parent[v] = u;
                    cycleId[v] = id;
                    cyclePos[v] = cyclePos[u];

                    depthXor[v] = depthXor[u] ^ V[v];
                    treeRoot[v] = trie.insert(treeRoot[u], depthXor[v]);

                    st.push_back(v);
                }
            }
        }

        vector<int> ans(N);

        for (int i = 0; i < N; ++i) {
            int id = cycleId[i];
            const CycleInfo &cy = cycles[id];

            int k = cyclePos[i];
            int target = depthXor[i] ^ cy.pref[k];

            int best = trie.maxXor(cy.rightRoot, cy.leftRoot, target);

            // Prefixes that stop before entering the cycle.
            if (!isCycle[i]) {
                best = max(best, depthXor[i]); // XOR against the cycle-root value 0
                if (parent[i] != -1) {
                    best = max(best,
                        trie.maxXor(treeRoot[parent[i]], 0, depthXor[i]));
                }
            }

            ans[i] = best;
        }

        for (int i = 0; i < N; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
}

int main() {
    int dinosauraus = 0;
    read_your_input();
    return 0;
}
