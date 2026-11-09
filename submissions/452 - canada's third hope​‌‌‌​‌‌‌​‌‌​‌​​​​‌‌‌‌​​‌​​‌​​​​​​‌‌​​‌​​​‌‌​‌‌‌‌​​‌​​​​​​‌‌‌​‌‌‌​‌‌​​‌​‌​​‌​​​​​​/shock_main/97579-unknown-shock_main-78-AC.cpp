#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int inf = 0x3F3F3F3F;
const ll infll = 0x3F3F3F3F3F3F3F3FLL;

ll sqrtf(ll x)
{
    ll y = sqrt(x);
	while (y*y > x) y--;
	while ((y+1)*(y+1) <= x) y++;
	return y;
}

void solve()
{
    int n, m, q; cin >> n >> m >> q;
    bool swp = 0;
    if (n > m) { swp = 1; swap(n, m); }
    vector<set<int>> a(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            a[i].insert(j);
    }
    vector<array<int, 3>> eq(q);
    for (int i = 0; i < q; i++) cin >> eq[i][0] >> eq[i][1] >> eq[i][2];
    vector<vll> ans(n, vll(m, 0));
    for (int qi = q-1; qi >= 0; qi--)
    {
        auto [r, c, p] = eq[qi];
        if (swp) swap(r, c);
        for (int i = r-p; i <= r+p; i++)
        {
            int dc = sqrtf(1LL*p*p - 1LL*(i-r)*(i-r));
            auto lb = a[i].lower_bound(c-dc);
            while (lb != a[i].end() && *lb <= c+dc)
            {
                int j = *lb; lb++;
                ans[i][j] = 1LL*p*p - 1LL*(i-r)*(i-r) - 1LL*(j-c)*(j-c) + 1;
                a[i].erase(j);
            }
        }
    }
    if (swp) swap(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (swp) cout << ans[j][i] << " ";
            else cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T-- > 0)
        solve();

    return 0;
}