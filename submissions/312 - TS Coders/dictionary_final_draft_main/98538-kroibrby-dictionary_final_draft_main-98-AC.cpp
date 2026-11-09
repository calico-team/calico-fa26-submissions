#include <bits/stdc++.h>
using namespace std;

struct Node { int ch[2] = {0, 0}; };

struct PersistentTrie {
    vector<Node> tr;
    PersistentTrie() { tr.emplace_back(); }
    int add(int root, int x) {
        int nr = (int)tr.size();
        tr.push_back(tr[root]);
        int cur = nr, old = root;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int oldChild = tr[old].ch[bit];
            int newChild = (int)tr.size();
            tr.push_back(tr[oldChild]);
            tr[cur].ch[bit] = newChild;
            cur = newChild;
            old = oldChild;
        }
        return nr;
    }
    int best(int root, int mask) const {
        int cur = root, value = 0;
        for (int b = 29; b >= 0; --b) {
            int bit = (mask >> b) & 1;
            int want = bit ^ 1;
            if (tr[cur].ch[want]) {
                value |= (1 << b);
                cur = tr[cur].ch[want];
            } else {
                cur = tr[cur].ch[bit];
            }
        }
        return value;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> to(n), indeg(n, 0), w(n);
        for (int &x : to) { cin >> x; --x; }
        for (int &x : w) cin >> x;
        for (int v : to) ++indeg[v];

        queue<int> q;
        for (int i = 0; i < n; ++i) if (!indeg[i]) q.push(i);
        vector<int> peeled;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            peeled.push_back(u);
            if (--indeg[to[u]] == 0) q.push(to[u]);
        }

        PersistentTrie trie;
        vector<int> root(n, 0), mask(n, 0), ans(n, 0);
        vector<char> seen(n, 0);

        for (int s = 0; s < n; ++s) {
            if (indeg[s] == 0 || seen[s]) continue;
            vector<int> cyc;
            int u = s;
            do { cyc.push_back(u); seen[u] = 1; u = to[u]; } while (u != s);

            int len = (int)cyc.size();
            vector<int> pref(len + 1, 0);
            for (int i = 0; i < len; ++i) pref[i + 1] = pref[i] ^ w[cyc[i]];
            int total = pref[len];
            int base = 0;
            for (int i = 1; i <= len; ++i) {
                base = trie.add(base, pref[i]);
                if (total) base = trie.add(base, pref[i] ^ total);
            }
            for (int i = 0; i < len; ++i) {
                int v = cyc[i];
                root[v] = base;
                mask[v] = pref[i];
                ans[v] = trie.best(base, mask[v]);
            }
        }

        for (int z = (int)peeled.size() - 1; z >= 0; --z) {
            int u = peeled[z], v = to[u];
            int oldMask = mask[v];
            mask[u] = oldMask ^ w[u];
            root[u] = trie.add(root[v], oldMask);
            ans[u] = trie.best(root[u], mask[u]);
        }

        for (int i = 0; i < n; ++i) cout << ans[i] << (i + 1 == n ? '\n' : ' ');
    }
}
