#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
char c[114514];
char ans[114514];
int main(){
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++)cin>>c[i],ans[i]=0;
		
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)cout<<c[i];cout<<'\n';
			cout<<flush;
			for(int j=1;j<=n;j++){
				char c;
				cin>>c;
				if(c!='_')ans[j]=c;
			}
		}
		
		for(int i=1;i<=n;i++)cout<<ans[i];cout<<'\n';
		string t;
		cin>>t;
	}
	return 0;
}

