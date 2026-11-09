#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m;
char c[105],a[105];
void szzakioi()
{
	cin>>n>>m;
	for(int I=1;I<=m;I++)
	{
		char i=getchar();
		while(!(i>='A'&&i<='Z')) i=getchar();
		a[I]=i;
	}
	for(int I=1;I<=m;I++)
	{
		char i=a[I];
		string g="";
		for(int j=1;j<=n;j++) g+=i;
		cout<<g<<endl;
		string res;
		cin>>res;
		for(int j=1;j<=n;j++)
			if(res[j-1]!='_') c[j]=i;
	}
	for(int i=1;i<=n;i++) cout<<c[i];
	string tt;cin>>tt;
}
int main()
{
	cin>>t;
	while(t--) szzakioi();
	return 0;
}
