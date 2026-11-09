#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int par[1000005];
int getr (int x) {return par[x] == x ? x : par[x] = getr(par[x]);}

void merge(int a, int b) {
    a = getr(a); b = getr(b);
    if (a != b) {
        if (a < b) swap(a, b);
        par[b] = a;
    }
}
int n, m, q; 
inline int conv(int x, int y) {
    return (x - 1) * m + y;
}

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> q;
        int r[q + 1], c[q + 1], p[q + 1];
        for (int i = 1; i <= q; i++) cin >> r[i] >> c[i] >> p[i], r[i]++, c[i]++;

        ll ans[n + 1][m + 1] = {0};
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    par[conv(i, j)] = conv(i, j);
                }
            }
        for (int i = q; i >= 1; i--) {
            if (n < m) {
                for (int j = r[i] - p[i]; j <= r[i] + p[i]; j++) {
                    ll avail = 1ll * p[i] * p[i] - 1ll * (r[i] - j) * (r[i] - j);
                    avail = sqrtl(avail);
                    int cur = c[i] - avail;
                    //cout << j << ' ' << cur << '\n';
                    
                    while (1) {
                        int x = getr(conv(j, cur));
                        int a = (x - 1) / m + 1, b = (x - 1) % m + 1;
                        if (b > c[i] + avail) break;
                        ans[j][b] = 1ll * p[i] * p[i] - 1ll * (r[i] - j) * (r[i] - j) - 1ll * (c[i] - b) * (c[i] - b) + 1;
                        //cout << i << ' ' << j << ' ' << b << ' ' << ans[j][b] << '\n';
                        //assert (ans[j][b] > 0);
                        if (b < m) merge(conv(j, cur), x + 1);
                        else break;
                    }
                    
                }
            }
            else {
                for (int j = c[i] - p[i]; j <= c[i] + p[i]; j++) {
                    ll avail = 1ll * p[i] * p[i] - 1ll * (c[i] - j) * (c[i] - j);
                    avail = sqrtl(avail);
                    int cur = r[i] - avail;
                    while (1) {
                        int x = getr(conv(cur, j));
                        int a = (x - 1) / m + 1, b = (x - 1) % m + 1;
                        if (a > r[i] + avail) break;
                        ans[a][j] = 1ll * p[i] * p[i] - 1ll * (c[i] - j) * (c[i] - j) - 1ll * (r[i] - a) * (r[i] - a) + 1;
                        //cout << i << ' ' << a << ' ' << j << ' ' << ans[a][j] << '\n';
                        //assert (ans[a][j] > 0);
                        if (a < n) merge(conv(cur, j), x + m);
                        else break;
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cout << ans[i][j] << ' ';
            cout << '\n';
        }
    }
}
