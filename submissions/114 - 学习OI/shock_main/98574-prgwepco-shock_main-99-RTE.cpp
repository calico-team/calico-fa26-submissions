#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 20010, M = 1000010;
ll n, m, q, x[N], y[N], p[N];
struct modif { ll l, r, id; };
vector<modif> q1[1010], L[M], R[M];
ll dist(ll ax, ll ay, ll bx, ll by) { return (ax-bx)*(ax-bx)+(ay-by)*(ay-by); }
void solve()
{
	scanf("%lld%lld%lld", &n, &m, &q);
	ll flag = (n > m); if (flag) swap(n, m);
	vector<vector<ll> > id(n, vector<ll>(m, 0));
	for (ll i = 0; i < n; i++) q1[i].clear();
	for (ll i = 1; i <= q; i++)
	{
		scanf("%lld%lld%lld", &x[i], &y[i], &p[i]);
		if (flag) swap(x[i], y[i]);
		ll L = max(0LL, x[i]-p[i]), R = min(n-1, x[i]+p[i]);
//		printf("%lld\n", i);
		for (ll j = L; j <= R; j++)
		{
			ll tmp = p[i]*p[i]-(j-x[i])*(j-x[i]);
			ll len = floor(sqrt(tmp));
//			printf("%lld %lld %lld\n", j, max(0LL, y[i]-len), min(m-1, y[i]+len));
			q1[j].push_back((modif){max(0LL, y[i]-len), min(m-1, y[i]+len), i});
		}
	}
	set<ll> st;
	for (ll i = 0; i < n; i++)
	{
		for (ll j = 0; j <= m; j++) L[j].clear(), R[j].clear();
		for (auto it : q1[i]) L[it.l].push_back(it), R[it.r+1].push_back(it);
		st.clear();
		for (ll j = 0; j < m; j++)
		{
			for (auto it : R[j]) st.erase(it.id);
			for (auto it : L[j]) st.insert(it.id);
			if (!st.size()) { id[i][j] = 0; continue; }
			auto it1 = st.end(); it1--;
			id[i][j] = *it1;
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
//染色，计算最后一个覆盖到每个点的地震是哪场 
//
