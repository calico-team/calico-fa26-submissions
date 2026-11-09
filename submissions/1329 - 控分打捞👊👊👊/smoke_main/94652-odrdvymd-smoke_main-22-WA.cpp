#include<bits/stdc++.h>
using namespace std;
const long long A=100000+1000;
int T,N,R,a[A],i;
int smoke_num=2;
int next_reload=0;
bool check()
{
	for(i=0;i<N;i++)
	{
		if(next_reload<=a[i] && smoke_num<2)
		{
			smoke_num++;
		}
		if(smoke_num==0)
		{
			return false;
		}
		smoke_num--;
		next_reload=a[i]+R;
	}
	return true;
}

int main()
{
	cin>>T;
	while(T--)
	{
		cin>>N>>R;
		smoke_num=2;
		next_reload=0;
		for(i=0;i<N;i++)
		{
			cin>>a[i];
		}
		if(check())
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0;
}
