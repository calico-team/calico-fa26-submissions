#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
ll t,n,m,k,ans,a[100005],d[100005];
vector<ll> e[100005];
priority_queue<pii> q;
void szzakioi()
{
	ans=0; 
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++) d[i]=0,a[i]=0,e[i].clear();
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		e[a[i]].push_back(i);
		d[a[i]]++;
	}
	for(int i=1;i<=n;i++)
		if(!a[i]) q.push({d[i],i});
	for(int i=1;i<=m;i++)
	{
		ll sz=q.size();
		vector<ll> p;
		for(int j=1;j<=min(sz,k);j++)
		{
			ans++;
			p.push_back(q.top().second);
			q.pop();
		}
		for(ll x:p)
			for(ll y:e[x]) q.push({d[y],y});
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%lld",&t);
	while(t--) szzakioi();
	return 0;
}
