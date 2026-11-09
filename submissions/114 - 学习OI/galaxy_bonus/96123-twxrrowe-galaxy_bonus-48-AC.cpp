#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m,q,fa[100005];
string s[205];
ll cg(ll x,ll y){return x*m+y;}
ll find(ll x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void unitee(ll x,ll y){fa[find(x)]=find(y);}
void szzakioi()
{
	cin>>n>>m>>q;
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<=n*m;i++) fa[i]=i;
	for(int i=0;i<n;i++)
		for(int j=0;j+1<m;j++)
		{
			if(s[i][j]=='R'&&s[i][j+1]=='B') continue;
			if(s[i][j]=='B'&&s[i][j+1]=='R') continue;
			unitee(cg(i,j),cg(i,j+1));
		}
	for(int i=0;i+1<n;i++)
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='R'&&s[i+1][j]=='B') continue;
			if(s[i][j]=='B'&&s[i+1][j]=='R') continue;
			unitee(cg(i,j),cg(i+1,j));
		}
	while(q--)
	{
		ll a=0,b=0,c=0,d=0;
		cin>>a>>b>>c>>d;
		if(find(cg(a,b))==find(cg(c,d))) printf("YES\n");
		else printf("NO\n");
	}
}
int main()
{
	cin>>t;
	while(t--) szzakioi();
	return 0;
}
