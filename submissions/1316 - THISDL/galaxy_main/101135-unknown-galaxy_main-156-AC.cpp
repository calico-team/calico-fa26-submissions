#include<bits/stdc++.h>
using namespace std;
const int N=210;

int n,m,Q;
char a[N][N];
int	f[N][N],vis[N*N];
int fx[5]={0,0,1,-1};
int fy[5]={1,-1,0,0};
vector <int> e[N*N*2];
bool check(char X,char Y){
	if(X=='.' || Y=='.') return true;
	if(X=='R' && Y=='R') return true;
	if(X=='B' && Y=='B') return true;
	return false;
}


void dfs(int u,int fa,int col){
	//cout<<u<<' '<<fa<<endl;
	vis[u]=col;
	for(int v:e[u]){
		if(v==fa) continue;
		if(vis[v]) continue;
		dfs(v,u,col);
	}
}

void solve(){
	memset(vis,0,sizeof(vis));
	cin>>n>>m>>Q;
	for(int i=0;i<=N*N;i++) e[i].clear();
	string st;
	for(int i=1;i<=n;i++){
		cin>>st;
		for(int j=0;j<m;j++){
			a[i][j+1]=st[j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=(i-1)*m+j;		
			int tx,ty;
			for(int k=0;k<4;k++){
				tx=i+fx[k];
				ty=j+fy[k];
				if(tx==0 || tx==n+1 || ty==0 || ty==m+1) continue;
				if(check(a[i][j],a[tx][ty])){
					e[f[i][j]].push_back((tx-1)*m+ty);
					e[(tx-1)*m+ty].push_back(f[i][j]);
					//cout<<i<<' '<<j<<" "<<tx<<" "<<ty<<endl;
				}
			}
			
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[f[i][j]]==0){
				cnt++;
				dfs((i-1)*m+j,0,cnt);
			}
		}
	}
	/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<vis[f[i][j]]<<" ";
		}
		cout<<endl;
	}
	*/
	int sx,sy,ex,ey;
	int start,en;
	while(Q--){
		cin>>sx>>sy>>ex>>ey;
		start=f[sx+1][sy+1],en=f[ex+1][ey+1];
		if(vis[start]==vis[en]){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
