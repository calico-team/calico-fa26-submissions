#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2];
    Node() { ch[0] = ch[1] = 0; }
};

const int B = 30;
vector<Node> trie;

int newNode() {
    trie.emplace_back();
    return (int)trie.size() - 1;
}

int insertTrie(int prev, int val) {
    int cur = newNode();
    trie[cur] = trie[prev];
    int curNode = cur;
    int prevNode = prev;
    for (int b = B; b >= 0; --b) {
        int bit = (val >> b) & 1;
        int prevChild = trie[prevNode].ch[bit];
        int curChild = newNode();
        trie[curChild] = trie[prevChild];
        trie[curNode].ch[bit] = curChild;
        curNode = curChild;
        prevNode = prevChild;
    }
    return cur;
}

int queryMax(int root, int tag) {
    int node = root;
    int ans = 0;
    for (int b = B; b >= 0; --b) {
        int bitTag = (tag >> b) & 1;
        int want = bitTag ^ 1;
        if (trie[node].ch[want]) {
            ans |= (1 << b);
            node = trie[node].ch[want];
        } else {
            node = trie[node].ch[bitTag];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N + 1);
        for (int i = 1; i <= N; ++i) cin >> A[i];
        vector<int> V(N + 1);
        for (int i = 1; i <= N; ++i) cin >> V[i];

        vector<int> indeg(N + 1, 0);
        for (int i = 1; i <= N; ++i) indeg[A[i]]++;
        queue<int> q;
        for (int i = 1; i <= N; ++i) if (indeg[i] == 0) q.push(i);
        vector<int> order;
        vector<char> removed(N + 1, 0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            removed[u] = 1;
            order.push_back(u);
            int v = A[u];
            if (--indeg[v] == 0) q.push(v);
        }

        trie.clear();
        trie.reserve((N * 4 + 5) * 32);
        trie.emplace_back();

        vector<int> rootVer(N + 1, 0);
        vector<int> tagVer(N + 1, 0);
        vector<long long> ans(N + 1, 0);
        vector<char> vis(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            if (removed[i] || vis[i]) continue;
            vector<int> cyc;
            int cur = i;
            while (!vis[cur]) {
                vis[cur] = 1;
                cyc.push_back(cur);
                cur = A[cur];
            }
            int k = (int)cyc.size();
            vector<int> pref(k + 1, 0);
            for (int j = 0; j < k; ++j) pref[j + 1] = pref[j] ^ V[cyc[j]];
            int Xc = pref[k];
            int r = 0;
            for (int j = 1; j <= k; ++j) {
                r = insertTrie(r, pref[j]);
                r = insertTrie(r, pref[j] ^ Xc);
            }
            rootVer[cyc[0]] = r;
            tagVer[cyc[0]] = 0;
            ans[cyc[0]] = queryMax(r, 0);

            for (int idx = k - 1; idx >= 1; --idx) {
                int node = cyc[idx];
                int nxt = cyc[(idx + 1) % k];
                int Told = tagVer[nxt];
                int Rold = rootVer[nxt];
                int Tnew = Told ^ V[node];
                int Rnew = insertTrie(Rold, Told);
                rootVer[node] = Rnew;
                tagVer[node] = Tnew;
                ans[node] = queryMax(Rnew, Tnew);
            }
        }

        for (int idx = (int)order.size() - 1; idx >= 0; --idx) {
            int u = order[idx];
            int v = A[u];
            int Told = tagVer[v];
            int Rold = rootVer[v];
            int Tnew = Told ^ V[u];
            int Rnew = insertTrie(Rold, Told);
            rootVer[u] = Rnew;
            tagVer[u] = Tnew;
            ans[u] = queryMax(Rnew, Tnew);
        }

        for (int i = 1; i <= N; ++i) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}