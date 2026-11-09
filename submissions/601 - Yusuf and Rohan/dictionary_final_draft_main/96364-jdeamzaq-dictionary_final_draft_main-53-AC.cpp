#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
    struct Node {
        int child[2] = {-1, -1};
        int count = 0;
    };

    vector<Node> nodes;

    BinaryTrie() {
        nodes.emplace_back();
    }

    void reset() {
        nodes.clear();
        nodes.emplace_back();
    }

    void insert(int x) {
        int p = 0;
        ++nodes[p].count;
        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            int next = nodes[p].child[b];
            if (next == -1) {
                next = (int)nodes.size();
                nodes[p].child[b] = next;
                nodes.emplace_back();
            }
            p = next;
            ++nodes[p].count;
        }
    }

    void erase(int x) {
        int p = 0;
        --nodes[p].count;
        for (int bit = 29; bit >= 0; --bit) {
            p = nodes[p].child[(x >> bit) & 1];
            --nodes[p].count;
        }
    }

    int bestXor(int x) const {
        int p = 0, ans = 0;
        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            int want = nodes[p].child[b ^ 1];
            if (want != -1 && nodes[want].count > 0) {
                ans |= (1 << bit);
                p = want;
            } else {
                p = nodes[p].child[b];
            }
        }
        return ans;
    }
};

struct Frame {
    int u, parent;
    bool exit;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1), v(n + 1), indeg(n + 1);
        vector<vector<int>> rev(n + 1);

        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            indeg[a[i]]++;
            rev[a[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i) {
            cin >> v[i];
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            indeg[a[u]]--;
            if (indeg[a[u]] == 0) {
                q.push(a[u]);
            }
        }

        vector<int> prefix(n + 1), ans(n + 1);
        vector<char> seen(n + 1, 0);
        BinaryTrie trie;
        vector<Frame> st;

        for (int i = 1; i <= n; ++i) {
            if (indeg[i] == 0 || seen[i]) continue;

            vector<int> cycle;
            int cur = i;
            do {
                cycle.push_back(cur);
                seen[cur] = 1;
                cur = a[cur];
            } while (cur != i);

            int cycleXor = 0;
            for (int u : cycle) {
                prefix[u] = cycleXor;
                cycleXor ^= v[u];
            }

            trie.reset();
            for (int u : cycle) {
                trie.insert(prefix[u]);
                if (cycleXor) {
                    trie.insert(prefix[u] ^ cycleXor);
                }
            }
            for (int u : cycle) {
                ans[u] = trie.bestXor(prefix[u]);
            }

            for (int root : cycle) {
                st.push_back({root, -1, false});
                while (!st.empty()) {
                    Frame f = st.back();
                    st.pop_back();

                    if (f.exit) {
                        trie.erase(prefix[f.parent]);
                        continue;
                    }

                    if (f.parent != -1) {
                        trie.insert(prefix[f.parent]);
                        prefix[f.u] = prefix[f.parent] ^ v[f.u];
                        ans[f.u] = trie.bestXor(prefix[f.u]);
                        st.push_back({f.u, f.parent, true});
                    }

                    for (int child : rev[f.u]) {
                        if (indeg[child] == 0) {
                            st.push_back({child, f.u, false});
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}
