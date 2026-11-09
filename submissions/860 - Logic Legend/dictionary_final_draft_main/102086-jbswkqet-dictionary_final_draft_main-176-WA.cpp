// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
    struct Node {
        int child[2];
        int cnt;

        Node() {
            child[0] = child[1] = -1;
            cnt = 0;
        }
    };

    vector<Node> trie;

    BinaryTrie() {
        trie.emplace_back();
    }

    void add(int x, int delta) {
        int node = 0;
        trie[node].cnt += delta;

        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;

            if (trie[node].child[b] == -1) {
                trie[node].child[b] = trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[b];
            trie[node].cnt += delta;
        }
    }

    int getMaxXor(int x) const {
        int node = 0;
        int result = 0;

        for (int bit = 29; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            int wanted = b ^ 1;

            if (trie[node].child[wanted] != -1 &&
                trie[trie[node].child[wanted]].cnt > 0) {
                result |= 1 << bit;
                node = trie[node].child[wanted];
            } else {
                node = trie[node].child[b];
            }
        }

        return result;
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

        vector<int> A(N), V(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            --A[i];
        }

        for (int i = 0; i < N; ++i) {
            cin >> V[i];
        }

        vector<vector<int>> reverseGraph(N);
        vector<int> indegree(N);

        for (int i = 0; i < N; ++i) {
            reverseGraph[A[i]].push_back(i);
            ++indegree[A[i]];
        }

        queue<int> q;
        vector<bool> inCycle(N, true);

        for (int i = 0; i < N; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            inCycle[u] = false;

            if (--indegree[A[u]] == 0) {
                q.push(A[u]);
            }
        }

        vector<int> answer(N);
        vector<int> prefix(N);
        vector<bool> visited(N);

        for (int start = 0; start < N; ++start) {
            if (!inCycle[start] || visited[start]) {
                continue;
            }

            vector<int> cycle;
            int current = start;

            do {
                cycle.push_back(current);
                visited[current] = true;
                current = A[current];
            } while (current != start);

            int L = cycle.size();
            vector<int> doubledPrefix(2 * L + 1);

            for (int i = 0; i < 2 * L; ++i) {
                doubledPrefix[i + 1] =
                    doubledPrefix[i] ^ V[cycle[i % L]];
            }

            BinaryTrie cycleTrie;

            for (int i = 1; i <= L; ++i) {
                cycleTrie.add(doubledPrefix[i], 1);
            }

            for (int i = 0; i < L; ++i) {
                answer[cycle[i]] =
                    cycleTrie.getMaxXor(doubledPrefix[i]);

                if (i + 1 < L) {
                    cycleTrie.add(doubledPrefix[i + 1], -1);
                    cycleTrie.add(doubledPrefix[i + L + 1], 1);
                }
            }

            vector<int> cyclePrefix(L + 1);

            for (int i = 0; i < L; ++i) {
                cyclePrefix[i + 1] =
                    cyclePrefix[i] ^ V[cycle[i]];
            }

            int cycleXor = cyclePrefix[L];

            BinaryTrie continuationTrie;

            for (int i = 0; i < L; ++i) {
                continuationTrie.add(cyclePrefix[i], 1);

                if (cycleXor != 0) {
                    continuationTrie.add(cyclePrefix[i] ^ cycleXor, 1);
                }
            }

            BinaryTrie ancestorTrie;
            ancestorTrie.add(0, 1);
            ancestorTrie.add(V[start], 1);

            struct State {
                int node;
                int index;
            };

            vector<State> stack;

            for (int child : reverseGraph[start]) {
                if (inCycle[child]) {
                    continue;
                }

                prefix[child] = V[start] ^ V[child];
                ancestorTrie.add(prefix[child], 1);

                answer[child] = max(
                    ancestorTrie.getMaxXor(prefix[child]),
                    continuationTrie.getMaxXor(prefix[child])
                );

                stack.push_back({child, 0});
            }

            while (!stack.empty()) {
                State &state = stack.back();
                int u = state.node;

                if (state.index < (int)reverseGraph[u].size()) {
                    int child = reverseGraph[u][state.index++];

                    if (inCycle[child]) {
                        continue;
                    }

                    prefix[child] = prefix[u] ^ V[child];
                    ancestorTrie.add(prefix[child], 1);

                    answer[child] = max(
                        ancestorTrie.getMaxXor(prefix[child]),
                        continuationTrie.getMaxXor(prefix[child])
                    );

                    stack.push_back({child, 0});
                } else {
                    ancestorTrie.add(prefix[u], -1);
                    stack.pop_back();
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (i) {
                cout << ' ';
            }
            cout << answer[i];
        }

        cout << '\n';
    }

    return 0;
}

