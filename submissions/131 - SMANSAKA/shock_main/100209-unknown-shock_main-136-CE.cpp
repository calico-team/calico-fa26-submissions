#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);

    int t; 
    if (!(cin >> t)) return0;
    while (t--) {
        int n,m,q; 
        cin >> n >>m >>q;

        // simpan query, offline pake reverse processing biar gampang
        vector<array<int, 3>> qry(q);
        for (int i= 0; i <q; ++i) {
            cin >> qry[i][0] >>qry[i][1] >>qry[i][2];
        }

        vector<vector<int>> ans(n,vector<int>(m, 0));
        int w = m +5;
        vector<int> d(n* w);
        for (int i =0; i <n * w; ++i) d[i] =i;

        //bismillah ac yaAllah
        auto get_root = [&](int x) {
            int root = x;
            while (root !=d[root]) root = d[root];
            int curr = x;
            while (curr !=root) {
                int nxt =d[curr];
                d[curr] =root;
                curr = nxt;
            }
            return root;
        };

        for (int i = q - 1; i >= 0; --i) {
            int r0 =qry[i][0];
            int c0 =qry[i][1];
            int p = qry[i][2];
            ll pp =1LL * p * p;

            int r_min =max(0, r0 - p);
            int r_max = min(n - 1, r0 + p);

            for (int r =r_min; r <= r_max; ++r) {
                ll dy =r - r0;
                ll z= pp - dy * dy;
                if (z <0) continue;
                int dx= (int)sqrtl(z);
                while(1LL * (dx + 1) * (dx + 1) <= z) ++dx;
                while (1LL * dx * dx > z) --dx;

                int l =max(0, c0 - dx);
                int rr =min(m - 1, c0 + dx);
                if (l >rr) continue;

                int base =r * w;
                int x =get_root(base + l);

                while (x<= base + rr) {
                    int c =x - base;
                    if (c >= m) break;
                    ll dc =c - c0;
                    ans[r][c] = (int)(pp - dy * dy - dc * dc + 1);
                    d[x] =get_root(x +1);
                    x = d[x];
                }
            }
        }

        // cetak hasil akhir sesuai format soal
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (c) cout << ' ';
                cout << ans[r][c];
            }
            cout << '\n';
        }
    }
    return 0;
}