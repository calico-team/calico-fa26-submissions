#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1e18;
const ll MOD = 1e9 + 7;
bool testcases = true;

template <int B = 30>
struct BinaryTrie {
    static_assert(1 <= B && B < 63);
    struct Node {
        int ch[2] = {-1, -1};
        int cnt = 0;
    };
    vector<Node> t;
    long long lazy = 0;
    BinaryTrie(int reserve_n = 0) {
        t.reserve((size_t)reserve_n * B + 1);
        t.emplace_back();
    }
    int size() const { return t[0].cnt; }
    bool empty() const { return t[0].cnt == 0; }
    void xor_all(long long x) {
        assert(0 <= x && x < (1LL << B));
        lazy ^= x;
    }
    void insert(long long x, int c = 1) {
        assert(0 <= x && x < (1LL << B));
        if (c == 0) return;
        x ^= lazy;
        int u = 0;
        t[u].cnt += c;
        for (int b = B - 1; b >= 0; --b) {
            int d = x >> b & 1;
            if (t[u].ch[d] == -1) {
                t[u].ch[d] = t.size();
                t.emplace_back();
            }
            u = t[u].ch[d];
            t[u].cnt += c;
        }
    }
    int count(long long x) const {
        assert(0 <= x && x < (1LL << B));
        x ^= lazy;
        int u = 0;
        for (int b = B - 1; b >= 0; --b) {
            u = t[u].ch[x >> b & 1];
            if (u == -1) return 0;
        }
        return t[u].cnt;
    }
    void erase(long long x) {
        if (count(x) > 0) insert(x, -1);
    }
    int go(int u, int d) const {
        int v = t[u].ch[d];
        return (v != -1 && t[v].cnt > 0) ? v : -1;
    }
    long long max_xor(long long x) const {
        assert(!empty());
        assert(0 <= x && x < (1LL << B));
        x ^= lazy;
        int u = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; --b) {
            int d = x >> b & 1;
            int v = go(u, d ^ 1);
            if (v != -1) res |= 1LL << b, u = v;
            else u = go(u, d);
        }
        return res;
    }
    long long min_xor(long long x) const {
        assert(!empty());
        assert(0 <= x && x < (1LL << B));
        x ^= lazy;
        int u = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; --b) {
            int d = x >> b & 1;
            int v = go(u, d);
            if (v != -1) u = v;
            else res |= 1LL << b, u = go(u, d ^ 1);
        }
        return res;
    }
    long long kth(int k, long long x = 0) const {
        assert(0 <= k && k < size());
        assert(0 <= x && x < (1LL << B));
        x ^= lazy;
        int u = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; --b) {
            int d = x >> b & 1;
            int v = go(u, d);  // Branch giving bit 0 in (y ^ x).
            int c = v == -1 ? 0 : t[v].cnt;
            if (k < c) u = v;
            else k -= c, res |= 1LL << b, u = go(u, d ^ 1);
        }
        return res;
    }
    int count_less(long long v, long long x = 0) const {
        assert(0 <= x && x < (1LL << B));
        if (v <= 0) return 0;
        if (v >= (1LL << B)) return size();
        x ^= lazy;
        int u = 0, res = 0;
        for (int b = B - 1; b >= 0 && u != -1; --b) {
            int d = x >> b & 1;
            if (v >> b & 1) {
                int w = go(u, d);
                if (w != -1) res += t[w].cnt;
                u = go(u, d ^ 1);
            } else {
                u = go(u, d);
            }
        }
        return res;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> arr(n), val(n);
    vector<vector<int>> children(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    for (int i = 0; i < n; i++) cin >> val[i];
    vector<bool> incycle(n, true);
    vector<int> indeg(n, 0);
    for (int i = 0; i < n; i++) indeg[arr[i]]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        incycle[u] = false;
        indeg[arr[u]]--;
        if (indeg[arr[u]] == 0) q.push(arr[u]);
    }
    for (int i = 0; i < n; i++) if (!incycle[i]) children[arr[i]].push_back(i);
    vector<bool> seen(n, false);
    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        if (seen[i] || !incycle[i]) continue;
        BinaryTrie<> bt;
        vector<int> cycle;
        int j = i;
        while (true) {
            seen[j] = true;
            cycle.push_back(j);
            j = arr[j];
            if (i == j) break;
        }
        int sz = cycle.size();
        vector<ll> pref(2*sz+1, 0);
        for (int k = 0; k < 2*sz; k++) pref[k+1] = pref[k] ^ val[cycle[k%sz]];
        for (int k = 1; k <= 2*sz; k++) bt.insert(pref[k]);
        for (int k = 0; k < sz; k++) {
            int c = cycle[k];
            ans[c] = bt.max_xor(0);
            auto dfs = [&](int u, auto&& dfs) -> void {
                bt.xor_all(val[u]);
                bt.insert(val[u]);
                ans[u] = bt.max_xor(0);
                for (int v : children[u]) dfs(v, dfs);
                bt.erase(val[u]);
                bt.xor_all(val[u]);
            };
            for (int u : children[c]) dfs(u, dfs);
            if (k + 1 < sz) bt.xor_all(val[c]);
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if (testcases) cin >> t;
    for (int i = 1; i <= t; i++) solve();
    return 0;
}