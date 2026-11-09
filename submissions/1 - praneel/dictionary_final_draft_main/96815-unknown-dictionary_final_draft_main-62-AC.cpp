#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

using namespace std;

const ll MOD = 1e9 + 7;

// just keeping this here in case i need it later
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(a, b % a);
}
void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    if(b < 0) b += MOD;

    while(e) {
        if(e&1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }

    return r;
}
struct TNode {
    int child[2] = {0, 0};
    int count = 0;
};
struct WaveMat {
    int n = 0;
    vector<vector<int>> zeros;
    vector<int> middle;
    void build(const vector<int>& vals) {
        n = sz(vals);
        zeros.assign(30, vector<int>(n + 1));
        middle.resize(30);

        vector<int> cur = vals, nxt(n);

        for(int level = 0; level < 30; ++level) {
            int bit = 29 - level;
            for(int i= 0; i < n; ++i)
                zeros[level][i + 1] = zeros[level][i] + (((cur[i] >> bit) & 1) == 0);

            middle[level] = zeros[level][n];
            int z = 0, o = middle[level];

            for(int x : cur) {
                if(((x >> bit) & 1) == 0) nxt[z++] = x;
                else nxt[o++] = x;
            }
            cur.swap(nxt);
        }
    }
    int maxXor(int l, int r, int x) const {
        int res = 0;
        for(int level = 0; level < 30; ++level) {
            int bit = 29 - level;
            int zl = zeros[level][l];
            int zr = zeros[level][r];
            int c0 = zr - zl;
            int c1 = (r - l) - c0;
            // CHECK THIS PLEASE PLEASeE JAONS
            int want = ((x >> bit) & 1) ^ 1;
            int chosen = (want == 0 ? c0 : c1) ? want : (want ^ 1);
            if(chosen != ((x >> bit) & 1)) res |= (1 << bit);

            if(chosen == 0) {
                l = zl;
                r = zr;
            }
            else {
                l = middle[level] + (l - zl);
                r = middle[level] + (r - zr);
            }
        }
// oh this got it nvm
        return res;
    }
};
void solve() {
    int n ;
    cin>> n;
    vector<int> a(n), v(n);
    for(int i =0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    for(int i =0; i < n; ++i) {
        cin >> v[i];
    }
    vector<vector<int>> rev(n);
    vector<int> indeg(n, 0);

    for(int i= 0; i < n; ++i) {
        rev[a[i]].pb(i);
        ++indeg[a[i]];
    }
    queue<int> q;
    for(int i =0; i < n; ++i) {
        if(indeg[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(--indeg[a[u]] == 0) q.push(a[u]);
    }
    vector<char> on_cyc(n, false), seen(n, false);
    for(int i= 0; i < n; ++i) on_cyc[i] = (indeg[i] > 0);

    vector<int> cyc_nodes, comp_st, comp_len;
    vector<int> cyc_pref(n), cyc_xor(n), rng_l(n), rng_r(n);
    vector<int> all_prefs;

    for(int i =0; i < n; ++i) {
        if(!on_cyc[i] || seen[i]) continue;

        int st = sz(cyc_nodes);
        int u = i;
        do {
            seen[u] = true;
            cyc_nodes.pb(u);
            u = a[u];
        } while(u != i);

        int len = sz(cyc_nodes) - st;
        int base = sz(all_prefs);

        vector<int> pref(2 * len + 1, 0);
        int cyc_tot = 0;
        for(int j =0; j < len; ++j)
            cyc_tot ^= v[cyc_nodes[st + j]];

        for(int j =0; j < 2 * len; ++j)
            pref[j + 1] = pref[j] ^ v[cyc_nodes[st + (j % len)]];

        for(int j= 0; j < 2 * len; ++j)
            all_prefs.pb(pref[j]);

        for(int j =0; j < len; ++j) {
            int node = cyc_nodes[st + j];
            cyc_pref[node] = pref[j];
            cyc_xor[node] = cyc_tot;
            rng_l[node] = base + j + 1;
            rng_r[node] = base + j + len + 1;
        }

        comp_st.pb(st);
        comp_len.pb(len);
    }
// is this how it is?
    WaveMat wavelet;
    wavelet.build(all_prefs);
    vector<int> ans(n);
    for(int node : cyc_nodes) {
        int x = cyc_pref[node];
        int l = rng_l[node], r = rng_r[node];
        ans[node] = max(wavelet.maxXor(l, r, x),
                        wavelet.maxXor(l, r, x ^ cyc_xor[node]));
    }
// YES CHECK DOCS
    vector<int> tail_xor(n), tail_rt(n), ent_cyc(n);
    vector<TNode> trie;
    trie.pb({});
    auto ins_val = [&](int rt, int val) {
        int new_rt = sz(trie);
        TNode cp = trie[rt];
        ++cp.count;
        trie.pb(cp);

        int old_node = rt, new_node = new_rt;
        for(int bit = 29; bit >= 0; --bit) {
            int b = (val >> bit) & 1;
            int old_ch = trie[old_node].child[b];

            int new_ch = sz(trie);
            TNode ch_cp = trie[old_ch];
            ++ch_cp.count;
            trie.pb(ch_cp);

            trie[new_node].child[b] = new_ch;
            old_node = old_ch;
            new_node = new_ch;
        }
        return new_rt;
    };
    auto max_xor_trie = [&](int rt, int val) {
        int res = 0, node = rt;
        for(int bit = 29; bit >= 0; --bit) {
            int b = (val >> bit) & 1;
            int want = b ^ 1;
            int ch = trie[node].child[want];

            if(trie[ch].count > 0) {
                res |= (1 << bit);
                node = ch;
            }
            else {
                node = trie[node].child[b];
            }
        }
        return res;
    };
    vector<int> stk, tree_nodes;
    for(int c = 0; c < sz(comp_st); ++c) {
        int st = comp_st[c];
        int len = comp_len[c];
        stk.clear();
        tree_nodes.clear();
        for(int j =0; j < len; ++j) {
            int cyc_node = cyc_nodes[st + j];
            for(int val_node : rev[cyc_node])
                if(!on_cyc[val_node]) stk.pb(val_node);
        }
        while(!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            tree_nodes.pb(u);
            for(int val_node : rev[u])
                if(!on_cyc[val_node]) stk.pb(val_node);
        }
        trie.clear();
        trie.pb({});
        int z_rt = ins_val(0, 0);
        for(int u : tree_nodes) {
            int par = a[u];
            if(on_cyc[par]) {
                tail_xor[u] = v[u];
                tail_rt[u] = z_rt;
                ent_cyc[u] = par;
            }
            else {
                tail_xor[u] = v[u] ^ tail_xor[par];
                tail_rt[u] = ins_val(tail_rt[par], tail_xor[par]);
                ent_cyc[u] = ent_cyc[par];
            }
            int best_tail = max_xor_trie(tail_rt[u], tail_xor[u]);
            int e = ent_cyc[u];
            int x = tail_xor[u] ^ cyc_pref[e];
            int l = rng_l[e], r = rng_r[e];
            int best_cyc = max(wavelet.maxXor(l, r, x),
                               wavelet.maxXor(l, r, x ^ cyc_xor[e]));
            ans[u] = max(best_tail, best_cyc);
        }
    }
    for(int i =0; i < n; ++i) {
        if(i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
int main() {
    fastio();

    int T;
    cin >> T;
// k im submitting
    while(T--) {
        solve();
    }

    return 0;
}