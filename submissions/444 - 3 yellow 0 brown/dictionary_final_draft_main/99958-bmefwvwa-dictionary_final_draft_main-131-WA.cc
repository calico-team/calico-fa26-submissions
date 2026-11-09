#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int K = 30;

struct trie : vector<array<int, 2>> {
    trie() : vector(2) {}
    int lz = 0;
    vector<int> cnt = vector<int>(2);
    void insert(int x) {
        x ^= lz;
        ++cnt[1];
        for (int u = 1, k = K; k --> 0; ) {
            int b = x >> k & 1;
            if (!at(u)[b]) {
                at(u)[b] = size();
                push_back({0, 0});
                cnt.push_back(0);
            }
            u = at(u)[b];
            ++cnt[u];
        }
    }
    void remove(int x) {
        x ^= lz;
        assert(cnt[1]);
        --cnt[1];
        for (int u = 1, k = K; k --> 0; ) {
            u = at(u)[x >> k & 1];
            assert(u && cnt[u]);
            --cnt[u];
        }
    }
    void XOR(int v) { lz ^= v; }
    int mx() {
        assert(cnt[1]);
        int r = 0;
        for (int k = K, u = 1; k --> 0; ) {
            if (cnt[at(u)[1 ^ (lz >> k & 1)]]) r ^= (1 << k), u = at(u)[1 ^ (lz >> k & 1)];
            else u = at(u)[lz >> k & 1];
        }
        return r;
    }
};

void ac() {
    int n; cin >> n;    
    vector<int> a(n + 1), h(n + 1);
    auto rg = vector(n + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rg[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> h[i];
    vector<bool> vis(n + 1);
    vector<int> ans(n + 1);
    vector<int> prv(n + 1);
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        trie tr;
        int u = i, nu = a[i];
        // find, first cycle in this cc
        while (u != nu) u = a[u], nu = a[a[nu]];
        int tot = 0;
        do {
            prv[a[u]] = u;
            tot ^= h[u = a[u]];
            vis[u] = true;
        } while (u != nu);
        int cur = 0;
        do {
            cur ^= h[u];
            tr.insert(cur);
            tr.insert(tot ^ cur);
            u = a[u];
        } while (u != nu);
        auto dfs = [&](auto &&f, int x) -> void {
            vis[x] = true; 
            if (x != nu) {
                tr.insert(0);
                tr.XOR(h[x]);
            }
            ans[x] = tr.mx();
            for (int &y : rg[x]) if (!vis[y]) {
                f(f, y);
            }
            tr.XOR(h[x]);
            tr.remove(0);
        };
        do {
            dfs(dfs, u);
            tr.XOR(h[u]);
            u = prv[u];
        } while (u != nu);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}