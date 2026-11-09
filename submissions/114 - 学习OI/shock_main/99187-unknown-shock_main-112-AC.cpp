#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 20010, M = 1000010;
ll n, m, q, x[N], y[N], p[N], fa[M];
int find(int x) { return (x == fa[x] ? x : fa[x] = find(fa[x])); }
ll dist(ll ax, ll ay, ll bx, ll by) { return (ax-bx)*(ax-bx)+(ay-by)*(ay-by); }
void solve()
{
    scanf("%lld%lld%lld", &n, &m, &q);
    ll flag = (n > m); if (flag) swap(n, m);
    vector<vector<int>> id(n, vector<int>(m, 0));
    for (ll i = 1; i <= q; i++)
    {
        scanf("%lld%lld%lld", &x[i], &y[i], &p[i]);
        if (flag) swap(x[i], y[i]);
    }
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j <= m; j++) fa[j] = j;
        for (ll k = q; k >= 1; k--)
        {
            if (abs(i-x[k]) > p[k]) continue;
            ll tmp = p[k]*p[k]-(i-x[k])*(i-x[k]);
            ll len = sqrt(tmp);
            ll l = max(0LL, y[k]-len), r = min(m-1, y[k]+len);
            for (ll j = find(l); j <= r; j = find(j)) id[i][j] = k, fa[j] = j+1;
        }
    }
    if (flag)
    {
        for (ll j = 0; j < m; j++, printf("\n"))
            for (ll i = 0; i < n; i++)
            {
                if (!id[i][j]) { printf("0 "); continue; }
                ll ttt = id[i][j];
                ll tmp = p[ttt]*p[ttt]-dist(x[ttt], y[ttt], i, j)+1;
                printf("%lld ", tmp);
            }
    }
    else
    {
        for (ll i = 0; i < n; i++, printf("\n"))
            for (ll j = 0; j < m; j++)
            {
                if (!id[i][j]) { printf("0 "); continue; }
                ll ttt = id[i][j];
                ll tmp = p[ttt]*p[ttt]-dist(x[ttt], y[ttt], i, j)+1;
                printf("%lld ", tmp);
            }
    }
}

int main()
{
    ll T = 1; scanf("%lld", &T);
    while (T--) solve();
    return 0;
}
