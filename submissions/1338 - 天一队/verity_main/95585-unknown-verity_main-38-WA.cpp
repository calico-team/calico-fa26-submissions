#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
char a[114514];
char ans[114514];
int main(){
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++)cin>>a[i];
		for(int i=1;i<=n;i++)ans[i]='0';
		
		string t;
		do{
			for(int i=1;i<=m;i++){
				for(int j=1;j<=n;j++){
					if(ans[j]!='0')
					{
						cout<<ans[j];
					}
					else
					{
						cout<<a[i];
					}
				}
				cout<<'\n';
				cout<<flush;
				for(int j=1;j<=n;j++){
					char c;
					cin>>c;
					if(c!='_')ans[j]=c;
				}
				int t=1;
				for(int j=1;j<=n;j++){
					if(ans[j]=='0')
					{
						t=0;
					}
				}
				if(t)
				{
					break;
				}
			}
			
		}while(t!="CORRECT");
		
	}
	return 0;
}

