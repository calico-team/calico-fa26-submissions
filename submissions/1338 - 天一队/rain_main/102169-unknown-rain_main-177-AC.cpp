#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n,k;
struct Node
{
	int y;
	char dir;
};
void solve()
{
	map<int,map<int,Node>> mp;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		char c;
		cin>>x>>y>>z>>c;
		mp[y+x][x].y=y;
		mp[y+x][x].dir=c;
	}
	int tmp=0;
	for(auto i:mp)
	{
		queue<int> q;
		int num=0;
		for(auto j:i.second)
		{
			int x=j.first;
			int y=j.second.y;
			char dir=j.second.dir;
			while(!q.empty()&&x-q.front()>k-1)
			{
				q.pop();
				num--;
			}
			if(dir=='E')
			{
				num++;
				q.push(x);
			}
			else
			{
				tmp+=num;
			}
		}
	}
	cout<<n*k-tmp<<'\n';
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
