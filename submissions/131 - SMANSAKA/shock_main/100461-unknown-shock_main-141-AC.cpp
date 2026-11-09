#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int t; 
    if (!(cin >>t)) return 0;
    while (t--) {
        int n, m,q; 
        cin >> n >> m>>q;

        struct E { int r,c,p; };
        vector<E> a(q);
        for (auto &e :a) cin >> e.r >> e.c >> e.p;

        vector<vector<int>>ans(n, vector<int>(m, 0));

        int w = m + 2;
        vector<int> d(n *w);
        iota(d.begin(), d.end(), 0);

        // bismillah ini pake interval maut :v
        auto f =[&](auto self, int x) -> int {
            int y =x;
            while (y!= d[y]) y = d[y];
            while (x !=y) {
                int z =d[x];
                d[x] =y;
                x= z;
            }
            return y;
        };

        // Balik urutan: gempa terakhir jadi yg pertama dieksekusi (offline query trick)
        for (int i = q - 1;i >=0; --i) {
            auto [r0, c0, p] =a[i];
            ll pp = 1LL *p * p;

            int rs =max(0, r0 -p);
            int re =min(n - 1, r0+ p);

            for (int r =rs; r <= re; ++r) {
                ll dy = r - r0;
                ll z= pp - dy *dy;
                if (z <0) continue;

                int dx =sqrtl(z);
                while (1LL *(dx +1) * (dx + 1) <= z) ++dx;
                while (1LL * dx *dx > z) --dx;

                int l = max(0,c0 - dx);
                int rr =min(m - 1, c0 + dx);
                if (l > rr) continue;

                int base = r* w;
                int x =f(f, base + l);

                while (x <=base + rr) {
                    int c= x - base;
                    ll dc =c - c0;

                    ans[r][c] =(int)(pp - dy * dy - dc * dc + 1);

                    d[x] = f(f, x + 1);
                    x = d[x];
                }
            }
        }

        // harusnya aman
        for (int r = 0; r< n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (c) cout << ' ';
                cout << ans[r][c];
            }
            cout << '\n';
        }
    }
    return 0;
}