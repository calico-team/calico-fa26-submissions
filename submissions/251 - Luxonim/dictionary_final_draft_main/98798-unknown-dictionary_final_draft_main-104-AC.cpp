#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int B;

struct Trie {
    vector<array<int,2>> ch;
    vector<int> c;
    void init() { ch.assign(1, {0,0}); c.assign(1, 0); }
    void ins(ll x, int d) {
        int p = 0;
        for (int b = B - 1; b >= 0; b--) {
            int k = (x >> b) & 1;
            if (!ch[p][k]) { ch[p][k] = ch.size(); ch.push_back({0,0}); c.push_back(0); }
            p = ch[p][k];
            c[p] += d;
        }
    }
    ll get(ll x) {
        int p = 0; ll r = 0;
        for (int b = B - 1; b >= 0; b--) {
            int k = (x >> b) & 1;
            int q = ch[p][k ^ 1];
            if (q && c[q] > 0) { r |= 1LL << b; p = q; }
            else p = ch[p][k];
        }
        return r;
    }
} cyc, tr;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n + 1);
        vector<ll> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        ll mx = 0;
        for (int i = 1; i <= n; i++) cin >> v[i], mx = max(mx, v[i]);
        B = 1;
        while ((1LL << B) <= mx) B++;

        vector<int> st(n + 1), inc(n + 1);
        for (int i = 1; i <= n; i++) {
            if (st[i]) continue;
            vector<int> pth;
            int x = i;
            while (!st[x]) st[x] = 1, pth.push_back(x), x = a[x];
            if (st[x] == 1) {
                int y = x;
                do inc[y] = 1, y = a[y]; while (y != x);
            }
            for (int p : pth) st[p] = 2;
        }

        vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n; i++) if (!inc[i]) g[a[i]].push_back(i);

        vector<ll> res(n + 1), d(n + 1);
        vector<int> vis(n + 1);
        tr.init();

        for (int s = 1; s <= n; s++) {
            if (!inc[s] || vis[s]) continue;
            vector<int> cy;
            int x = s;
            do cy.push_back(x), vis[x] = 1, x = a[x]; while (x != s);
            int m = cy.size();
            vector<ll> pre(m + 1);
            for (int i = 0; i < m; i++) pre[i + 1] = pre[i] ^ v[cy[i]];
            ll C = pre[m];

            cyc.init();
            for (int i = 0; i < m; i++) cyc.ins(pre[i], 1), cyc.ins(pre[i] ^ C, 1);

            for (int i = 0; i < m; i++) {
                int r = cy[i];
                ll sh = pre[i];
                res[r] = cyc.get(sh);
                d[r] = 0;
                tr.ins(0, 1);
                vector<pair<int,int>> stk = {{r, 0}};
                while (!stk.empty()) {
                    auto &[u, j] = stk.back();
                    if (j < (int)g[u].size()) {
                        int w = g[u][j++];
                        d[w] = d[u] ^ v[w];
                        res[w] = max(tr.get(d[w]), cyc.get(d[w] ^ sh));
                        tr.ins(d[w], 1);
                        stk.push_back({w, 0});
                    } else {
                        tr.ins(d[u], -1);
                        stk.pop_back();
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) cout << res[i] << " \n"[i == n];
    }
}
