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
int lf;
int isf,iss;
int ts=0;
void solve()
{
	isf=0;
	iss=0;
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
				cout<<"No\n";
				return;
			}
			iss=1;
			ts=r;
		}
		else
		{
			if(a[i]-lf>=r+ts)
			{
				isf=0;
				iss=0;
			}
			else
			{
				isf=0;
				ts=a[i]-lf-r;
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
