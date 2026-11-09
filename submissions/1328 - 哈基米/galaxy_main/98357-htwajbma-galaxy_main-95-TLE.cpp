#include<bits/stdc++.h>
using namespace std;
int flag,co,t,n,m,Q,sx,sy,ex,ey,tail,head,tf; 
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
	tail=0,head=0,tf=0;
	q[tail].x=sx,q[tail].y=sy,q[tail].co=0,tail++;
	mapp[sx][sy][0]=1;
	while(head<tail){
		int xx=q[head].x,xy=q[head].y,xc=q[head].co;
		if(xx==ex&&xy==ey){
			tf=1;
			return ;
		}
		if(grid[xx][xy]=='.'&&!mapp[xx][xy][xc^1]){
			mapp[xx][xy][xc^1]=1;
			q[tail].x=xx,q[tail].y=xy,q[tail].co=xc^1,tail++;
		}
		for(int i=0;i<4;i++){
			int nx=xx+dx[i],ny=xy+dy[i];
			if(nx>=0&&nx<n&&ny>=0&&ny<m&&!mapp[nx][ny][xc]&&active(grid[nx][ny],xc)){
				mapp[nx][ny][xc]=1;
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
			cin>>sx>>sy>>ex>>ey;
			memset(mapp,0,sizeof(mapp));
			bfs();
			if(tf==1)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
