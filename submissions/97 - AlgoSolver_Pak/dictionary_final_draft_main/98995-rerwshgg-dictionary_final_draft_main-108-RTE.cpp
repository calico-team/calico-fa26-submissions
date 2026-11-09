#include <bits/stdc++.h>
using namespace std;

struct Trie {
    vector<array<int,2>> nxt;
    Trie() { nxt.reserve(8000000); nxt.push_back({0, 0}); }

    int newNode(int prev) {
        if (prev == 0) nxt.push_back({0, 0});
        else nxt.push_back(nxt[prev]);
        return (int)nxt.size() - 1;
    }
    // insert val into version prev, return new root
    int insertNode(int prev, int val) {
        int newRoot = newNode(prev);
        int curNew = newRoot;
        int curPrev = prev;
        for (int b = 29; b >= 0; --b) {
            int bit = (val >> b) & 1;
            int childPrev = curPrev ? nxt[curPrev][bit] : 0;
            int childNew = newNode(childPrev);
            nxt[curNew][bit] = childNew;
            curNew = childNew;
            curPrev = childPrev;
        }
        return newRoot;
    }
    // max of (stored ^ xr)
    int queryMax(int root, int xr) {
        if (root == 0) return 0;
        int res = 0;
        int cur = root;
        for (int b = 29; b >= 0; --b) {
            int tagBit = (xr >> b) & 1;
            int want = 1 ^ tagBit;
            int go = nxt[cur][want];
            if (go != 0) {
                res |= (1 << b);
                cur = go;
            } else {
                int go2 = nxt[cur][want ^ 1];
                if (go2 == 0) break;
                cur = go2;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N + 1);
        for (int i = 1; i <= N; i++) cin >> A[i];
        vector<int> V(N + 1);
        for (int i = 1; i <= N; i++) cin >> V[i];

        vector<int> indeg(N + 1, 0);
        for (int i = 1; i <= N; i++) indeg[A[i]]++;

        queue<int> q;
        for (int i = 1; i <= N; i++) if (indeg[i] == 0) q.push(i);
        vector<int> rem;
        rem.reserve(N);
        vector<char> inCyc(N + 1, 1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inCyc[u] = 0;
            rem.push_back(u);
            int v = A[u];
            if (--indeg[v] == 0) q.push(v);
        }

        Trie trie;
        vector<int> verRoot(N + 1, 0), verTag(N + 1, 0), ans(N + 1, 0);
        vector<char> visCyc(N + 1, 0);

        // cycles
        for (int i = 1; i <= N; i++) if (inCyc[i] && !visCyc[i]) {
            vector<int> cyc;
            int cur = i;
            while (!visCyc[cur]) {
                visCyc[cur] = 1;
                cyc.push_back(cur);
                cur = A[cur];
            }
            int L = (int)cyc.size();
            vector<int> cycRoot(L), cycTag(L);
            int curRoot = 0, curTag = 0;
            for (int idx = 3 * L - 1; idx >= 0; --idx) {
                int node = cyc[idx % L];
                int val = V[node];
                int newTag = val ^ curTag;
                int newRoot = trie.insertNode(curRoot, curTag);
                if (idx < L) {
                    cycRoot[idx] = newRoot;
                    cycTag[idx] = newTag;
                }
                curRoot = newRoot;
                curTag = newTag;
            }
            for (int j = 0; j < L; j++) {
                int node = cyc[j];
                verRoot[node] = cycRoot[j];
                verTag[node] = cycTag[j];
                ans[node] = trie.queryMax(cycRoot[j], cycTag[j]);
            }
        }

        // tree nodes, cycle se bahar ki taraf
        for (int idx = (int)rem.size() - 1; idx >= 0; --idx) {
            int u = rem[idx];
            int v = A[u];
            int newTag = V[u] ^ verTag[v];
            int newRoot = trie.insertNode(verRoot[v], verTag[v]);
            verRoot[u] = newRoot;
            verTag[u] = newTag;
            ans[u] = trie.queryMax(newRoot, newTag);
        }

        for (int i = 1; i <= N; i++) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}