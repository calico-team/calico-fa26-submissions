#include<iostream>
#include<algorithm>

using namespace std;

constexpr int N=205*205+5;
constexpr int G=205;

#define int long long 

int q,n,m;
int fa[N];
int fnd(int x){
	return fa[x]==x?x:fa[x]=fnd(fa[x]);
}
inline int pos(int x,int y){
	return m*(x-1)+y;
}
inline bool same(int x,int y){
	return fnd(x)==fnd(y);
}
inline void merge(int x,int y){
	fa[fnd(x)]=fnd(y);
}
char g[G][G];

int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};


/*
100*(200*200)
*/

namespace tqy{
	inline void init(){
		cin>>n>>m>>q;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>g[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				fa[pos(i,j)]=pos(i,j);
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				for(int k=0;k<4;++k){
					int ii=i+dx[k];
					int jj=j+dy[k];
					if(1<=ii&&ii<=n&&1<=jj&&jj<=m&&(g[i][j]=='.'||g[ii][jj]=='.'||g[i][j]==g[ii][jj])){
						if(!same(pos(ii,jj),pos(i,j))){
							merge(pos(ii,jj),pos(i,j));
						}
					}
				}
			}
		}
		
	}
	inline void solve(){
		for(int i=1;i<=q;++i){
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			++x1,++y1,++x2,++y2;
			cout<<(same(pos(x1,y1),pos(x2,y2))?"YES":"NO")<<'\n';
		}
	}
}

signed main(){
	int T;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--)tqy::init(),tqy::solve();
	return 0;
}