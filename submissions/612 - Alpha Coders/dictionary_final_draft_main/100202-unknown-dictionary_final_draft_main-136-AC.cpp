
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct BinaryTrie {
    struct Node {
        int ch[2] = {-1, -1};
        int cnt = 0;
    };

    vector<Node> t;

    BinaryTrie() {
        t.emplace_back();
    }

    void clear() {
        t.clear();
        t.emplace_back();
    }

    void update(int x, int delta) {
        int u = 0;
        t[u].cnt += delta;

        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;

            if (t[u].ch[bit] == -1) {
                t[u].ch[bit] = (int)t.size();
                t.emplace_back();
            }

            u = t[u].ch[bit];
            t[u].cnt += delta;
        }
    }

    int maxXor(int x) const {
        if (t[0].cnt == 0) return 0;

        int u = 0;
        int result = 0;

        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;

            int nxt = t[u].ch[want];

            if (nxt != -1 && t[nxt].cnt > 0) {
                result |= (1 << b);
                u = nxt;
            } else {
                u = t[u].ch[bit];
            }
        }

        return result;
    }
};

struct Event {
    int u;
    int parentXor;
    int value;
    bool exit;
};

/**
 * Return an array of N integers, the i-th of which
 * represents Big Ben's maximum happiness if he
 * starts by trying to define word i.
 *
 * N: the number of words in the dictionary
 * A: the first word in the definition of word i
 * V: the value associated with the happiness of each word
 */
vector<int> solve(int N, vector<int> A, vector<int> V) {

    int dinosauraus = N;
    (void)dinosauraus;

    // Convert A to zero-based indexing.
    for (int &x : A) --x;

    // Build reverse graph and indegrees.
    vector<vector<int>> rev(N);
    vector<int> indeg(N, 0);

    for (int i = 0; i < N; ++i) {
        rev[A[i]].push_back(i);
        indeg[A[i]]++;
    }

    // Find all vertices belonging to directed cycles.
    vector<bool> isCycle(N, true);
    queue<int> q;

    for (int i = 0; i < N; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        isCycle[u] = false;

        int v = A[u];
        indeg[v]--;

        if (indeg[v] == 0) {
            q.push(v);
        }
    }

    vector<int> ans(N, 0);
    vector<bool> seen(N, false);

    BinaryTrie cycleTrie, pathTrie;
    vector<Event> st;

    // Process every directed cycle.
    for (int i = 0; i < N; ++i) {

        if (!isCycle[i] || seen[i])
            continue;

        // Extract the cycle.
        vector<int> cycle;
        int u = i;

        while (!seen[u]) {
            seen[u] = true;
            cycle.push_back(u);
            u = A[u];
        }

        int L = (int)cycle.size();

        // Prefix XORs over three cycle traversals.
        vector<int> P(3 * L + 1, 0);

        for (int j = 0; j < 3 * L; ++j) {
            P[j + 1] = P[j] ^ V[cycle[j % L]];
        }

        // Initial cycle window:
        // P[1], P[2], ..., P[2L].
        cycleTrie.clear();

        for (int j = 1; j <= 2 * L; ++j) {
            cycleTrie.update(P[j], +1);
        }

        // Process each cycle vertex.
        for (int s = 0; s < L; ++s) {

            int c = cycle[s];

            // For the cycle vertex itself.
            ans[c] = cycleTrie.maxXor(P[s]);

            // Initialize the trie containing XOR prefixes
            // of ancestors in the current attached tree.
            pathTrie.clear();
            pathTrie.update(0, +1);

            st.clear();

            // Start DFS from non-cycle children of c.
            for (int child : rev[c]) {
                if (!isCycle[child]) {
                    st.push_back({
                        child, 0, 0, false
                    });
                }
            }

            while (!st.empty()) {

                Event e = st.back();
                st.pop_back();

                // Remove the current vertex when leaving it.
                if (e.exit) {
                    pathTrie.update(e.value, -1);
                    continue;
                }

                int u = e.u;

                // XOR of vertices from the child of c to u.
                int curXor = e.parentXor ^ V[u];

                // Option 1: Stop somewhere in the tree.
                int bestTree = pathTrie.maxXor(curXor);

                // Option 2: Continue into the cycle.
                int bestCycle = cycleTrie.maxXor(
                    curXor ^ P[s]
                );

                ans[u] = max(bestTree, bestCycle);

                // Insert current prefix XOR.
                pathTrie.update(curXor, +1);

                // Schedule rollback after processing children.
                st.push_back({
                    u, 0, curXor, true
                });

                // Visit non-cycle children.
                for (int child : rev[u]) {
                    if (!isCycle[child]) {
                        st.push_back({
                            child, curXor, 0, false
                        });
                    }
                }
            }

            // Slide cycle window for the next starting vertex.
            if (s + 1 < L) {
                cycleTrie.update(P[s + 1], -1);
                cycleTrie.update(P[s + 2 * L + 1], +1);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N), V(N);

        for (int &i : A) cin >> i;
        for (int &i : V) cin >> i;

        vector<int> ans = solve(N, A, V);

        for (int &i : ans) cout << i << ' ';
        cout << '\n';
    }

    return 0;
}
