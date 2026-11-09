#include<bits/stdc++.h>
using namespace std;

vector<array<int, 2>> trie;


int insert(int root, int x) {
    int newRoot = trie.size();
    trie.push_back(trie[root]);
    int cur = newRoot;

    for (int bit = 29; bit >= 0; bit--) {
        int b = (x >> bit) & 1;
        int next = trie[root][b];
        int node = trie.size();
        trie.push_back(trie[next]);
        trie[cur][b] = node;
        cur = node;
        root = next;
    }

    return newRoot;
}

int maxXor(int root, int x) {
    int ans = 0;

    for (int bit = 29; bit >= 0; bit--) {
        int b = (x >> bit) & 1;
        if (trie[root][1 - b] != 0) {
            ans |= (1 << bit);
            root = trie[root][1 - b];
        } else {
            root = trie[root][b];
        }
    }

    return ans;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<int> a(n + 1), v(n + 1), indegree(n + 1, 0);
        vector<int> prefix(n + 1), root(n + 1), ans(n + 1);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            indegree[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
        }

        
        queue<int> q;
        vector<int> order;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            indegree[a[u]]--;
            if (indegree[a[u]] == 0) q.push(a[u]);
        }

        trie.clear();
        trie.reserve(62 * n + 1);
        trie.push_back({0, 0});

        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) continue;

            vector<int> cycle;
            int u = i;
            int sum = 0;

            do {
                cycle.push_back(u);
                indegree[u] = 0;
                prefix[u] = sum;
                sum ^= v[u];
                u = a[u];
            } while (u != i);

            
            int cycleRoot = 0;
            for (int node : cycle) {
                cycleRoot = insert(cycleRoot, prefix[node]);
                if (sum != 0) {
                    cycleRoot = insert(cycleRoot, prefix[node] ^ sum);
                }
            }

            for (int node : cycle) {
                root[node] = cycleRoot;
                ans[node] = maxXor(cycleRoot, prefix[node]);
            }
        }

        
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            prefix[u] = v[u] ^ prefix[a[u]];
            root[u] = insert(root[a[u]], prefix[u]);
            ans[u] = maxXor(root[u], prefix[u]);
        }

        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], i == n ? '\n' : ' ');
        }
    }

    return 0;
}
