#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n,r;
int a[N];
int lf,ls=-INF;
int isf,iss;
void solve()
{
	isf=0;
	iss=0;
	lf=-INF;
	ls=-INF;
	cin>>n>>r;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	lf=a[1];
	isf=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]-lf<r)
		{
			if(iss==1)
			{
				cout<<iss<<"No\n";
				return;
			}
			ls=a[i];
			iss=1;
		}
		else
		{
			if(a[i]-lf>=r*2)
			{
				isf=0;
				iss=0;
			}
			lf=a[i];
			isf=1;
		}
	}
	cout<<"Yes\n";
	return;
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
