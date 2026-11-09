#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m;
char c[105];
void szzakioi()
{
	cin>>n>>m;
	string tt;
	for(int i=1;i<=m;i++) cin>>tt;
	for(char i='A';i<='Z';i++)
	{
		string g="";
		for(int j=1;j<=n;j++) g+=i;
		cout<<g<<endl;
		string res;
		cin>>res;
		for(int j=1;j<=n;j++)
			if(res[j-1]!='_') c[j]=i;
	}
	for(int i=1;i<=n;i++) cout<<c[i];
}
int main()
{
	cin>>t;
	while(t--) szzakioi();
	return 0;
}
