
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define abysr ios_base::sync_with_stdio(0); cin.tie(0);

string mymap[205];
int par[80005];

int dy[] = {0, 1};
int dx[] = {1, 0};

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a != b) {
        par[a] = b;
    }
}

int main() {
    abysr

    ll t;
    cin >> t;

    while (t--) {
        ll n, m, q;
        cin >> n >> m >> q;

        for (int i = 0; i < n; i++) {
            cin >> mymap[i];
        }

        ll sz = n * m;

        for (int i = 0; i < 2 * sz; i++) {
            par[i] = i;
        }

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {

                ll now = y * m + x;

                for (int i = 0; i < 2; i++) {
                    ll ty = y + dy[i];
                    ll tx = x + dx[i];

                    if (ty >= n || tx >= m) continue;

                    ll next = ty * m + tx;

                    if (mymap[y][x] != 'R' && mymap[ty][tx] != 'R') {
                        unite(now, next);
                    }

                    if (mymap[y][x] != 'B' && mymap[ty][tx] != 'B') {
                        unite(sz + now, sz + next);
                    }
                }

                if (mymap[y][x] == '.') {
                    unite(now, sz + now);
                }
            }
        }

        while (q--) {
            ll rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;

            ll start = rs * m + cs;
            ll finish = re * m + ce;

            ll awal = find(start);
            ll tujuan;

            if (mymap[re][ce] == 'R') {
                tujuan = find(sz + finish);
            } else {
                tujuan = find(finish);
            }

            if (awal == tujuan) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }

    return 0;
}
