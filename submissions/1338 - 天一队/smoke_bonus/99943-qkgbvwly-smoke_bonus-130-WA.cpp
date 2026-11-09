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
int store;
queue<int> q;
void solve()
{
	store=2;
	cin>>n>>r;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(!q.empty())
	{
		q.pop();
	}
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&q.front()<=a[i])
        {
            q.pop();
            store++;
        }
        if(store==0)
        {
            cout<<i<<"NO\n";
            return;
        }
        store--;
        if(q.empty())
        {
        	q.push(a[i]+r);
		}
		else
		{
			q.push(q.back()+r);
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
