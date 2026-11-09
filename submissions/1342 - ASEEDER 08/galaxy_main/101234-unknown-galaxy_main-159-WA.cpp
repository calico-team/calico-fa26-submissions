#include<bits/stdc++.h>
using namespace std;
int flag,co,t,n,m,Q,sx,sy,ex,ey,tail,head,tf,cnt; 
char grid[205][205];
int mapp[205][205][2];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
struct node{
	int x,y,co;
}q[100005];
bool active(char ch,int co){
	if(ch=='.')return true;
	if(ch=='B')return co==0;
	return co==1;
}
void bfs(){
	cnt=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int k=0;k<2;k++){
				if(mapp[i][j][k]||!active(grid[i][j],k))continue;
				head=0,tail=0,cnt++;
				mapp[i][j][k]=cnt;
				q[tail].x=i,q[tail].y=j,q[tail].co=k,tail++;
				while(head<tail){
					int xx=q[head].x,xy=q[head].y,xc=q[head].co;
					if(grid[xx][xy]=='.'&&!mapp[xx][xy][xc^1]){
						mapp[xx][xy][xc^1]=cnt;
						q[tail].x=xx,q[tail].y=xy,q[tail].co=xc^1,tail++;
						
					}
					for(int l=0;l<4;l++){
						int nx=xx+dx[l],ny=xy+dy[l];
						if(nx>=0&&nx<n&&ny>=0&&ny<m&&!mapp[nx][ny][xc]&&active(grid[nx][ny],xc)){
							mapp[nx][ny][xc]=cnt;
							q[tail].x=nx,q[tail].y=ny,q[tail].co=xc,tail++;
						}
					}	
					head++;
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m>>Q;
		for(int i=0;i<n;i++){
			cin>>grid[i];
		}
		memset(mapp,0,sizeof(mapp));
		bfs();
		for(int i=1;i<=Q;i++){
			tf=0;
			cin>>sx>>sy>>ex>>ey;
			if(mapp[ex][ey][0]==mapp[sx][sy][0])tf=1;
			if(mapp[ex][ey][1]==mapp[sx][sy][0])tf=1;
			if(tf==1)cout<<"YES"<<"/n";
			else cout<<"NO"<<"/n";
		}
	}
	return 0;
}
