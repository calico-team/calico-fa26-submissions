#include<bits/stdc++.h>
using namespace std;
const long long A=100000+1000;
int T,N,R,a[A],i;
int smoke_num=2;
int next_reload[2]={0,0};
int tmp=0;
bool check()
{
	next_reload[0]=a[0]+R;
	smoke_num--;
	if(next_reload[0]<=a[1])
	{
		smoke_num++;
		next_reload[0]=0;
	}
	else
	{
		next_reload[1]=a[0]+2*R;
		smoke_num--;
	}
	for(i=2;i<N;i++)
	{
		if(next_reload[0]<=a[i])
		{
			smoke_num++;
			next_reload[0]=next_reload[1];
			next_reload[1]=0;
		}
		if(smoke_num==0)
		{
			return false;
		}
		smoke_num--;
		next_reload[1]=a[i]+2*R;
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
		next_reload[0]=0;
		next_reload[1]=0;
		next_reload[2]=0;
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
