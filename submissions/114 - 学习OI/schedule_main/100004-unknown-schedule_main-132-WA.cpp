#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<pii,ll> piii;
ll t,n,m,k,ans,a[100005],d[100005],sz[100005];
vector<ll> e[100005];
struct nodee
{
	ll x,y,z;
	bool operator<(const nodee &aa)const
	{
		if(x==aa.x) return y<aa.y;
		return x<aa.x;
	}
};
priority_queue<nodee> q;
void dfs(ll x){sz[x]=1;for(int v:e[x])sz[x]+=sz[v];}
void szzakioi()
{
	ans=0; 
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=0;i<=n;i++) sz[i]=0,d[i]=0,a[i]=0,e[i].clear();
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		e[a[i]].push_back(i);
		d[a[i]]++;
	}
	dfs(0);
	for(int i=1;i<=n;i++)
		if(!a[i]) q.push({sz[i],d[i],i});
	for(int i=1;i<=m;i++)
	{
		ll szz=q.size();
		vector<ll> p;
		for(int j=1;j<=min(szz,k);j++)
		{
			ans++;
			p.push_back(q.top().z);
			q.pop();
		}
		for(ll x:p)
			for(ll y:e[x]) q.push((nodee){sz[y],d[y],y});
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%lld",&t);
	while(t--) szzakioi();
	return 0;
}
