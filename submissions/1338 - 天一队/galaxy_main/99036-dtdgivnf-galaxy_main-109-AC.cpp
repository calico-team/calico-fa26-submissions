#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
char mp[205][205];
int block[205][205];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int n,m;
void bfs(int stx,int sty,int c){
	queue<pair<int,int> >q;
	q.push(make_pair(stx,sty));
	block[stx][sty]=c;
	while(q.size()){
		auto f=q.front();q.pop();
		int x=f.first,y=f.second;
		for(int i=0;i<4;i++){
			int xx=x+dir[i][0];
			int yy=y+dir[i][1];
			if(xx<1||n<xx||yy<1||m<yy)continue;
			if(block[xx][yy])continue;
			if(mp[x][y]=='R'&&mp[xx][yy]=='B')continue;
			if(mp[x][y]=='B'&&mp[xx][yy]=='R')continue;
			block[xx][yy]=c;
			q.push(make_pair(xx,yy));
		}
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int q;
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>mp[i][j],block[i][j]=0;
		
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!block[i][j])
					bfs(i,j,++cnt);
		
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<block[i][j]<<' ';
			cout<<'\n';
		}*/
		
		while(q--){
			int stx,sty,edx,edy;
			cin>>stx>>sty>>edx>>edy;
			stx++;sty++;edx++;edy++;
			cout<<(block[stx][sty]==block[edx][edy]?
				"YES\n":"NO\n");
		}
	}
	return 0;
}
/*
3
2 4 2
.R.B
.RRB
0 0 1 3
1 0 1 3
2 4 2
.RB.
.RB.
0 0 1 3
0 3 1 3
9 9 3
BR.R.R.R.
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
B.B.B.B.B
8 1 8 8
0 4 8 8
8 7 8 8
*/ 
