#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,fa[100000],tot,u,v,t1,t2;
string mp[305];
bool vis[305][305];
int xx[5]={-1,0,0,1};
int yy[5]={0,-1,1,0};
int id(int i,int j){
	return m*(i-1)+j;
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void dfs(int x,int y,char c){
//	cout<<"dfs:"<<x<<' '<<y<<' '<<c<<endl;
	for(int i=0;i<4;i++){
		int tx=x+xx[i],ty=y+yy[i];
//		cout<<"try: "<<x<<' '<<y<<" -> "<<tx<<' '<<ty<<endl;
		if(tx<1||ty<1||tx>n||ty>m) continue;
//		cout<<"pass1\n";
		if(vis[tx][ty]) continue;
//		cout<<"pass2\n";
		if(mp[tx][ty]!=c&&mp[tx][ty]!='.') continue;
//		cout<<x<<' '<<y<<" to "<<tx<<' '<<ty<<endl;
		u=find(id(x,y));
		v=find(id(tx,ty));
		if(u!=v) fa[u]=v;
		vis[tx][ty]=1;
		dfs(tx,ty,c);
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++){
			cin>>mp[i];
			mp[i]=' '+mp[i];
			for(int j=1;j<=m;j++) fa[id(i,j)]=id(i,j);
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!vis[i][j]&&mp[i][j]!='R')
					vis[i][j]=1,dfs(i,j,'B');
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!vis[i][j]&&mp[i][j]!='B')
					vis[i][j]=1,dfs(i,j,'R');
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=m;j++)
//				cout<<find(id(i,j))<<' ';
//			cout<<endl;
//		}
		int tar=find(id(n,m));
		for(int i=1;i<=q;i++){
			cin>>u>>v>>t1>>t2;
			u++,v++;
			if(find(id(u,v))==tar) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}