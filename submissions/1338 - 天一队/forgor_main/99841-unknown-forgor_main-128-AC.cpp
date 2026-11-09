#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
vector<int> G[214514];
int fa[214514];
void dfs(int cur,int f){
	fa[cur]=f;
	for(int i:G[cur])
		if(i!=f)dfs(i,cur);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	string s;
	cin>>s;
	if(s=="FIRST"){
		int n;
		cin>>n;
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1,0);
		for(int i=2;i<=n;i++)fa[1]^=fa[i];
		for(int i=1;i<=n;i++)cout<<fa[i]<<' ';
	}else{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>fa[i];
		if(fa[1]==-1);
		else{
			int idx=0;
			int tmp=fa[1];
			for(int i=2;i<=n;i++)
				if(fa[i]==-1)idx=i;
				else{
					tmp^=fa[i];
				}
			fa[idx]=tmp;
			
		}
		for(int i=2;i<=n;i++)
			cout<<i<<' '<<fa[i]<<'\n';
	}
	return 0;
}
/*
0 1 1

-1 1 1
*/
