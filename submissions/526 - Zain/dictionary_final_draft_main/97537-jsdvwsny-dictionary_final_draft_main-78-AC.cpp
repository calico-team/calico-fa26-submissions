
#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
    struct Node {
        int next[2];
        int count;
        Node() : next{-1, -1}, count(0) {}
    };

    vector<Node> trie;

    BinaryTrie() { trie.emplace_back(); }

    void clear() {
        trie.clear();
        trie.emplace_back();
    }

    void add(int x, int delta) {
        int u = 0;
        trie[u].count += delta;

        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = (int)trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
            trie[u].count += delta;
        }
    }

    int maxXor(int x) const {
        int u = 0, result = 0;

        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            int preferred = trie[u].next[b ^ 1];

            if (preferred != -1 &&
                trie[preferred].count > 0) {
                result |= (1 << bit);
                u = preferred;
            } else {
                u = trie[u].next[b];
            }
        }
        return result;
    }
};

struct Event {
    int u, offset, pref;
    bool leaving;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n), v(n), indegree(n, 0);
        vector<vector<int>> reverseEdges(n);

        for (int &x : a) {
            cin >> x;
            --x;
        }
        for (int &x : v) cin >> x;

        for (int u = 0; u < n; ++u) {
            reverseEdges[a[u]].push_back(u);
            ++indegree[a[u]];
        }

        queue<int> q;
        vector<char> isCycle(n, true), seen(n, false);

        for (int u = 0; u < n; ++u)
            if (indegree[u] == 0)
                q.push(u);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            isCycle[u] = false;

            if (--indegree[a[u]] == 0)
                q.push(a[u]);
        }

        vector<int> answer(n), prefixBefore(n);
        BinaryTrie cycleTrie, pathTrie;
        vector<Event> stack;

        for (int start = 0; start < n; ++start) {
            if (!isCycle[start] || seen[start])
                continue;

            vector<int> cycle;
            int u = start, totalXor = 0;

            do {
                seen[u] = true;
                cycle.push_back(u);
                prefixBefore[u] = totalXor;
                totalXor ^= v[u];
                u = a[u];
            } while (u != start);

            cycleTrie.clear();

            for (int c : cycle) {
                cycleTrie.add(prefixBefore[c], 1);
                cycleTrie.add(
                    prefixBefore[c] ^ totalXor, 1
                );
            }

            pathTrie.clear();
            pathTrie.add(0, 1);

            for (int c : cycle) {
                answer[c] =
                    cycleTrie.maxXor(prefixBefore[c]);

                stack.clear();

                for (int child : reverseEdges[c])
                    if (!isCycle[child])
                        stack.push_back({
                            child, prefixBefore[c], 0, false
                        });

                while (!stack.empty()) {
                    Event e = stack.back();
                    stack.pop_back();

                    if (e.leaving) {
                        pathTrie.add(e.pref, -1);
                        continue;
                    }

                    int pref = e.pref ^ v[e.u];

                    int bestTail = pathTrie.maxXor(pref);
                    int bestCycle = cycleTrie.maxXor(
                        pref ^ e.offset
                    );

                    answer[e.u] = max(bestTail, bestCycle);

                    pathTrie.add(pref, 1);
                    stack.push_back({
                        e.u, e.offset, pref, true
                    });

                    for (int child : reverseEdges[e.u])
                        stack.push_back({
                            child, e.offset, pref, false
                        });
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }

    return 0;
}
