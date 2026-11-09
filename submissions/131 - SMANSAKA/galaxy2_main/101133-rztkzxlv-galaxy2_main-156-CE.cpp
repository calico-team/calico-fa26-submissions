#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Sep {
    int l, r, sz;
    vector<int>bag, d;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int n,m,q; cin >> n >> m >> q;
        vector<string> g(n);
        for (auto &s :g) cin >> s;
        int nm = n *m, V = 2 * nm;

        vector<array<char, 2>> ok(nm);
        for (int r = 0; r <n;r++) for (int c = 0; c < m; c++) {
            int x = r *m + c;
            ok[x][0] =(g[r][c] != 'R');
            ok[x][1]=(g[r][c] != 'B');
        }

        vector<Sep> sp(m);
        vector<int> par(m,-1), dep(m), seen(V, 0), ds(V, 0), qu;
        qu.reserve(V);
        int tim = 0;

        //coba pke stack iteratifny jd manual
        vector<int> st_l,st_r,st_p,st_d;
        st_l.push_back(0);st_r.push_back(m- 1); st_p.push_back(-1); st_d.push_back(0);

        while (!st_l.empty()) {
            int l = st_l.back(), r =st_r.back(), p = st_p.back(), d = st_d.back();
            st_l.pop_back();st_r.pop_back(); st_p.pop_back(); st_d.pop_back();
            if (l > r) continue;
            int c = (l +r) >>1;
            par[c] =p;dep[c] = d;

            Sep &s =sp[c];
            s.l = l; s.r =r;

            for (int i = 0; i <n; i++) {
                int x = i * m +c;
                if (ok[x][0])s.bag.push_back(x);
                if (ok[x][1])s.bag.push_back(nm + x);
            }

            s.sz =(int)s.bag.size();
            int len =r - l + 1;
            s.d.assign((size_t)2 * n * len * s.sz, -1);

            for (int z =0; z < s.sz; z++) {
                ++tim;
                qu.clear();

                int st =s.bag[z];
                seen[st]= tim;
                ds[st] =0;
                qu.push_back(st);

                for (int h =0; h < (int)qu.size(); h++) {
                    int u= qu[h], md =(u >= nm), x = u - md * nm;
                    int rr =x /m, cc = x - rr * m;

                    int at = (md * n *len + rr * len + (cc - l)) * s.sz + z;
                    s.d[at] =ds[u];

                    int v;
                    if (rr && ok[x -m][md]) {
                        v = u -m;
                        if (seen[v] !=tim)
                            seen[v]= tim, ds[v] = ds[u] + 1, qu.push_back(v);
                    }

                    if (rr + 1 < n &&ok[x + m][md]) {
                        v = u +m;
                        if (seen[v] != tim)
                            seen[v] =tim, ds[v] = ds[u] + 1, qu.push_back(v);
                    }

                    if (cc > l && ok[x -1][md]) {
                        v = u - 1;
                        if (seen[v] !=tim)
                            seen[v]= tim, ds[v] = ds[u] + 1, qu.push_back(v);
                    }

                    if (cc < r&& ok[x +1][md]) {
                        v = u +1;
                        if (seen[v] !=tim)
                            seen[v]= tim, ds[v] = ds[u] + 1, qu.push_back(v);
                    }

                    if (g[rr][cc]== '.') {
                        v =(md ? u - nm : u + nm);
                        if (seen[v] != tim)
                            seen[v] =tim, ds[v] = ds[u] + 1, qu.push_back(v);
                    }
                }
            }

            st_l.push_back(c + 1); st_r.push_back(r); st_p.push_back(c); st_d.push_back(d + 1);
            st_l.push_back(l); st_r.push_back(c - 1); st_p.push_back(c); st_d.push_back(d + 1);
        }

        int LG = 1;
        while ((1 <<LG) <=m) LG++;

        vector<vector<int>> up(LG, vector<int>(m, -1));

        for (int c = 0; c <m; c++)
            up[0][c] =par[c];

        for (int j = 1; j <LG; j++) {
            for (int c = 0; c < m; c++) {
                int x = up[j-1][c];
                if (x != -1) up[j][c] = up[j - 1][x];
            }
        }

        auto lca = [&](int a, int b) {
            if (dep[a]<dep[b]) swap(a, b);

            int dif =dep[a] - dep[b];
            for (int j =0; j < LG; j++)
                if (dif >>j & 1) a = up[j][a];

            if (a == b) return a;

            for (int j =LG - 1; j >= 0; j--) {
                if (up[j][a] != up[j][b])
                    a = up[j][a], b =up[j][b];
            }

            return par[a];
        };

        while (q--) {
            int rs,cs, rt, ct;
            ll k;
            cin >> rs>> cs>rt >> ct >> k;

            int xt = rt * m+ ct;
            int a = cs, b =ct, z = lca(a, b);

            bool yes =0;
            int t0 = -1, t1 = -1;

            if (ok[xt][0]) t0 =0;
            if (ok[xt][1]) t1 =1;

            for (int c = z; c != -1 && !yes; c = par[c]) {
                Sep &s = sp[c];

                int len= s.r - s.l + 1, sz = s.sz;

                int is =(rs * len + (cs - s.l)) *sz;

                int it0 = (t0 == -1 ? -1 :
                    (t0 * n * len + rt * len + (ct - s.l))* sz);

                int it1 = (t1 == -1 ? -1 :
                    (t1 * n * len + rt * len + (ct - s.l)) *sz);

                for (int j = 0; j <sz; j++) {
                    int x = s.d[is+ j];
                    if (x < 0) continue;

                    int y =(it0 == -1 ? -1 : s.d[it0 + j]);
                    int w =(it1 == -1 ? -1 : s.d[it1 + j]);

                    if (w >= 0&& (y < 0 || w < y)) y = w;

                    if (y >=0 && (ll)x + y <= k) {
                        yes = 1;
                        break;
                    }
                }
            }

            cout << (yes ? "YES\n" : "NO\n");
        }
    }

    return 0;
}