#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

class XorTrie {
    vector<array<int, 2>> nodes;

public:
    struct Insertion {
        int parent, branch, size;
    };

    explicit XorTrie(int n) {
        int capacity = 1;
        for (int bit = 1; bit <= 30; ++bit) capacity += min(1 << bit, 2 * n);
        nodes.reserve(capacity);
    }

    void clear() {
        nodes.assign(1, {});
    }

    Insertion insert(int value) {
        int node = 0;
        Insertion insertion{-1, 0, 0};
        for (int bit = 29; bit >= 0; --bit) {
            int branch = (value >> bit) & 1;
            if (nodes[node][branch] == 0) {
                int index = nodes.size();
                if (insertion.parent == -1) insertion = {node, branch, index};
                nodes[node][branch] = index;
                nodes.push_back({});
            }
            node = nodes[node][branch];
        }
        return insertion;
    }

    void undo(Insertion insertion) {
        if (insertion.parent == -1) return;
        nodes[insertion.parent][insertion.branch] = 0;
        nodes.resize(insertion.size);
    }

    int best(int value) const {
        int node = 0, result = 0;
        for (int bit = 29; bit >= 0; --bit) {
            int branch = (value >> bit) & 1;
            int other = nodes[node][branch ^ 1];
            if (other) {
                result |= 1 << bit;
                node = other;
            } else {
                node = nodes[node][branch];
            }
        }
        return result;
    }
};

struct Frame {
    int child, prefix;
    XorTrie::Insertion insertion;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        vector<int> next(n), value(n), indegree(n), head(n, -1), sibling(n);
        for (int i = 0; i < n; ++i) {
            cin >> next[i];
            int to = --next[i];
            ++indegree[to];
            sibling[i] = head[to];
            head[to] = i;
        }
        for (int& x : value) cin >> x;

        vector<int> order;
        order.reserve(n);
        for (int i = 0; i < n; ++i)
            if (indegree[i] == 0) order.push_back(i);
        for (size_t i = 0; i < order.size(); ++i) {
            int to = next[order[i]];
            if (--indegree[to] == 0) order.push_back(to);
        }

        XorTrie trie(n);
        vector<int> cycle, prefix, answer(n);
        vector<Frame> stack;
        for (int start = 0; start < n; ++start) {
            if (indegree[start] <= 0) continue;
            cycle.clear();
            prefix.clear();
            int total = 0;
            for (int v = start; indegree[v] > 0; v = next[v]) {
                indegree[v] = -1;
                cycle.push_back(v);
                prefix.push_back(total);
                total ^= value[v];
            }

            trie.clear();
            for (int x : prefix) {
                trie.insert(x);
                if (total != 0) trie.insert(x ^ total);
            }

            for (size_t i = 0; i < cycle.size(); ++i) {
                int root = cycle[i];
                answer[root] = trie.best(prefix[i]);
                stack.push_back({head[root], prefix[i], {-1, 0, 0}});
                while (!stack.empty()) {
                    Frame& frame = stack.back();
                    int v = frame.child;
                    if (v == -1) {
                        trie.undo(frame.insertion);
                        stack.pop_back();
                        continue;
                    }
                    frame.child = sibling[v];
                    if (indegree[v] != 0) continue;
                    int x = frame.prefix ^ value[v];
                    answer[v] = trie.best(x);
                    stack.push_back({head[v], x, trie.insert(x)});
                }
            }
        }

        for (int i = 0; i < n; ++i) cout << answer[i] << (i + 1 == n ? '\n' : ' ');
    }
}
