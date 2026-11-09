
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int child[2] = {0, 0};
    int cnt = 0;
};

vector<Node> trie;

int insertValue(int root, int value) {
    int newRoot = (int)trie.size();
    trie.push_back(trie[root]);
    trie[newRoot].cnt++;

    int oldNode = root;
    int newNode = newRoot;

    for (int bit = 29; bit >= 0; --bit) {
        int b = (value >> bit) & 1;
        int oldChild = trie[oldNode].child[b];
        int newChild = (int)trie.size();

        trie.push_back(trie[oldChild]);
        trie[newChild].cnt++;
        trie[newNode].child[b] = newChild;

        oldNode = oldChild;
        newNode = newChild;
    }

    return newRoot;
}

int maximumXor(int leftRoot, int rightRoot, int x) {
    int result = 0;

    for (int bit = 29; bit >= 0; --bit) {
        int b = (x >> bit) & 1;
        int wanted = b ^ 1;

        int lc = trie[leftRoot].child[wanted];
        int rc = trie[rightRoot].child[wanted];

        if (trie[rc].cnt - trie[lc].cnt > 0) {
            result |= (1 << bit);
            leftRoot = lc;
            rightRoot = rc;
        } else {
            leftRoot = trie[leftRoot].child[b];
            rightRoot = trie[rightRoot].child[b];
        }
    }

    return result;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nxt(n), val(n), indegree(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> nxt[i];
        --nxt[i];
        ++indegree[nxt[i]];
    }

    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }

    queue<int> q;
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);
        int v = nxt[u];

        if (--indegree[v] == 0) {
            q.push(v);
        }
    }

    vector<int> leftRoot(n, 0), rightRoot(n, 0);
    vector<int> lazy(n, 0), ans(n, 0);
    vector<char> seen(n, false);

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0 || seen[i]) continue;

        vector<int> cyc;
        int u = i;
        int totalXor = 0;

        while (!seen[u]) {
            seen[u] = true;
            cyc.push_back(u);
            totalXor ^= val[u];
            u = nxt[u];
        }

        int len = (int)cyc.size();
        int limit = (totalXor == 0 ? len : 2 * len);
        int maxIndex = len - 1 + limit;

        vector<int> pref(maxIndex + 1, 0);

        for (int k = 0; k < maxIndex; ++k) {
            pref[k + 1] = pref[k] ^ val[cyc[k % len]];
        }

        vector<int> roots(maxIndex + 2, 0);

        for (int k = 0; k <= maxIndex; ++k) {
            roots[k + 1] = insertValue(roots[k], pref[k]);
        }

        for (int j = 0; j < len; ++j) {
            int node = cyc[j];

            leftRoot[node] = roots[j + 1];
            rightRoot[node] = roots[j + limit + 1];
            lazy[node] = pref[j];

            ans[node] = maximumXor(
                leftRoot[node],
                rightRoot[node],
                lazy[node]
            );
        }
    }

    for (int k = (int)order.size() - 1; k >= 0; --k) {
        int u = order[k];
        int v = nxt[u];

        lazy[u] = lazy[v] ^ val[u];
        leftRoot[u] = leftRoot[v];

        rightRoot[u] = insertValue(
            rightRoot[v],
            val[u] ^ lazy[u]
        );

        ans[u] = maximumXor(
            leftRoot[u],
            rightRoot[u],
            lazy[u]
        );
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }

    cout << '\n';
}

void read_your_input() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    trie.reserve(6500000);
    trie.push_back(Node());

    int dinosauraus = 0;

    read_your_input();

    return dinosauraus;
}
