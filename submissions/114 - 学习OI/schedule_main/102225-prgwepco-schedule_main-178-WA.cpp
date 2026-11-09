#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll N = 50010;
ll n, m, k, p[N], cnt[N], col[N];
vector<ll> g[N];
void solve()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	for (ll i = 1; i <= m; i++) cnt[i] = k;
	for (ll i = 1; i <= n; i++) scanf("%lld", &p[i]), g[i].clear();
	for (ll i = 1; i <= n; i++) col[i] = 0;
	for (ll i = 1; i <= n; i++)
		if (p[i]) g[p[i]].push_back(i);
	priority_queue<pll, vector<pll>, greater<pll> > q;
	for (ll i = 1; i <= n; i++)
		if (!p[i]) q.push({0, i});
	ll ret = 0;
	while (!q.empty())
	{
		pll f = q.top(); q.pop();
		ll u = f.second, cc = f.first;
		ll nxt = cc+1;
		while (nxt <= m && !cnt[nxt]) nxt++;
		if (nxt <= m) col[u] = nxt, cnt[nxt]--, ret++;
		if (col[u])
		{
			for (auto v : g[u]) q.push({col[u], v});
		}
	}
	printf("%lld\n", ret);
}

int main()
{
    ll T = 1; scanf("%lld", &T);
    while (T--) solve();
    return 0;
}
