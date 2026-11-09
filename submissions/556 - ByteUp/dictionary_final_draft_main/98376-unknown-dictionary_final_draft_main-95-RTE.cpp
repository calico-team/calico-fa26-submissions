#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct TrieNode {
    int left = -1;
    int right = -1;
    int cnt = 0;
};

struct Trie {
    vector<TrieNode> nodes;
    Trie() { nodes.emplace_back(); }

    void add(long long x, int delta, int bits) {
        int node = 0;
        nodes[node].cnt += delta;
        for (int b = bits - 1; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int &nxt = (bit == 0) ? nodes[node].left : nodes[node].right;
            if (nxt == -1) {
                nxt = nodes.size();
                nodes.emplace_back();
            }
            node = nxt;
            nodes[node].cnt += delta;
        }
    }

    long long query(long long x, int bits) {
        if (nodes[0].cnt == 0) return 0;
        int node = 0;
        long long result = 0;
        for (int b = bits - 1; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int preferred = (bit == 1) ? nodes[node].left : nodes[node].right;
            if (preferred != -1 && nodes[preferred].cnt > 0) {
                result |= (1LL << b);
                node = preferred;
            } else {
                node = (bit == 1) ? nodes[node].right : nodes[node].left;
            }
        }
        return result;
    }
};

void solve() {
    int N;
    if (!(cin >> N)) return;

    vector<int> A(N);
    vector<long long> V(N);
    long long max_v = 1;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        A[i]--; // 0-based indexing
    }
    for (int i = 0; i < N; ++i) {
        cin >> V[i];
        max_v = max(max_v, V[i]);
    }

    int bits = 0;
    while ((1LL << bits) <= max_v) bits++;
    bits = max(bits, 1);

    vector<vector<int>> rev(N);
    vector<int> indeg(N, 0);
    for (int i = 0; i < N; ++i) {
        rev[A[i]].push_back(i);
        indeg[A[i]]++;
    }

    vector<int> q;
    for (int i = 0; i < N; ++i) if (indeg[i] == 0) q.push_back(i);

    vector<bool> removed(N, false);
    int q_ptr = 0;
    while (q_ptr < (int)q.size()) {
        int u = q[q_ptr++];
        removed[u] = true;
        int p = A[u];
        indeg[p]--;
        if (indeg[p] == 0) q.push_back(p);
    }

    vector<long long> ans(N, 0);
    vector<bool> visited(N, false);

    for (int start = 0; start < N; ++start) {
        if (removed[start] || visited[start]) continue;

        vector<int> cycle;
        int u = start;
        while (!visited[u]) {
            visited[u] = true;
            cycle.push_back(u);
            u = A[u];
        }

        int L = cycle.size();
        vector<long long> prefix(3 * L + 1, 0);
        for (int j = 0; j < 3 * L; ++j) {
            prefix[j + 1] = prefix[j] ^ V[cycle[j % L]];
        }

        Trie cycle_trie;
        for (int j = 1; j <= 2 * L; ++j) cycle_trie.add(prefix[j], 1, bits);

        for (int i = 0; i < L; ++i) {
            int root = cycle[i];
            long long base = prefix[i];
            ans[root] = max(0LL, cycle_trie.query(base, bits));

            Trie tree_trie;
            tree_trie.add(0, 1, bits);
            vector<tuple<int, long long, int>> stack;

            for (int child : rev[root]) {
                if (removed[child]) stack.emplace_back(child, V[child], 0);
            }

            while (!stack.empty()) {
                auto [node, x, stage] = stack.back();
                stack.pop_back();

                if (stage == 1) {
                    tree_trie.add(x, -1, bits);
                    continue;
                }

                ans[node] = max({0LL, tree_trie.query(x, bits), cycle_trie.query(x ^ base, bits)});
                tree_trie.add(x, 1, bits);
                stack.emplace_back(node, x, 1);

                for (int child : rev[node]) {
                    if (removed[child]) stack.emplace_back(child, x ^ V[child], 0);
                }
            }

            if (i + 1 < L) {
                cycle_trie.add(prefix[i + 1], -1, bits);
                cycle_trie.add(prefix[i + 2 * L + 1], 1, bits);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << (i + 1 == N ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}
