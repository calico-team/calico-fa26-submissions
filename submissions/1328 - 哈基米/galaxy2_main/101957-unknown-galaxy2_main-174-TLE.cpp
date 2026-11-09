#include<bits/stdc++.h>
using namespace std;
int flag,co,t,n,m,Q,sx,sy,ex,ey,tail,head,tf,cnt,k;
char grid[15][4005];
int mapp[15][4005][2];      
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
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			mapp[i][j][0]=-1;
			mapp[i][j][1]=-1;
		}
	}
	head=0,tail=0;
	mapp[sx][sy][0]=0;               
	q[tail].x=sx,q[tail].y=sy,q[tail].co=0,tail++;
	while(head<tail){
		int xx=q[head].x,xy=q[head].y,xc=q[head].co;
		if(grid[xx][xy]=='.'&&mapp[xx][xy][xc^1]==-1){
			mapp[xx][xy][xc^1]=mapp[xx][xy][xc]+1;
			q[tail].x=xx,q[tail].y=xy,q[tail].co=xc^1,tail++;
		}
		for(int zzzzzzzz=0;zzzzzzzz<4;zzzzzzzz++){
			int nx=xx+dx[zzzzzzzz],ny=xy+dy[zzzzzzzz];
			if(nx>=0&&nx<n&&ny>=0&&ny<m&&mapp[nx][ny][xc]==-1&&active(grid[nx][ny],xc)){
				mapp[nx][ny][xc]=mapp[xx][xy][xc]+1;
				q[tail].x=nx,q[tail].y=ny,q[tail].co=xc,tail++;
			}
		}
		head++;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n>>m>>Q;
		for(int i=0;i<n;i++){
			cin>>grid[i];
		}
		for(int i=1;i<=Q;i++){
			tf=0;
			cin>>sx>>sy>>ex>>ey>>k;
			bfs();                             
			if(mapp[ex][ey][0]!=-1&&mapp[ex][ey][0]<=k)tf=1; 
			if(mapp[ex][ey][1]!=-1&&mapp[ex][ey][1]<=k)tf=1; 
			if(tf==1)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
