#include<bits/stdc++.h>
using namespace std;
#define int long long

int f[210][210],vis[210][210][2];
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
struct node{
	int x,y,mode;
};
//0:R 1:B

bool check(int i,int j,int mode){
	if(f[i][j]==0) return 1;
	else if(f[i][j]==1) return (mode==0);
	return (mode==1);
}

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char c;
				cin>>c;
				if(c=='.') f[i][j]=0;
				else if(c=='R') f[i][j]=1;
				else f[i][j]=2;
			}
		}
		memset(vis,0,sizeof(vis));
		queue<node>q;
		q.push({n,m,1});
		q.push({n,m,0});
		while(q.size()){
			node u=q.front();
			vis[u.x][u.y][u.mode]=1;
			q.pop();
			for(int i=0;i<4;i++){
				int x=u.x+dx[i],y=u.y+dy[i],mode=u.mode;
				if(x<=0 || x>n || y<=0 || y>m) continue;
				if((vis[x][y][0]|vis[x][y][1])==1) continue;
				if(check(x,y,mode)){
					q.push({x,y,mode});
				}
				if(f[u.x][u.y]==0){
					mode=1-mode;
					if(check(x,y,mode)){
						q.push({x,y,mode});
					}
				}
			}
		}
		while(k--){
			int x,y,allen1,allen2;
			cin>>x>>y>>allen1>>allen2;
			if((vis[x+1][y+1][1]|vis[x+1][y+1][0])==1) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0; 
}



//N:y++
//E:x++
//x[i]+k==x[j] && y[i]==y[j]+k
//k==x[j]-x[i]==y[i]-y[j]
//if(x[i]+y[i]==y[j]+x[j])
/*
x
> 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 > 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 ^ 0 0
0 0 0 0 0 ^ 0
0 0 0 0 0 0 0 y
*/
