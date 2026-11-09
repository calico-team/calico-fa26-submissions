#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
char c[205][205];
pair<int,int> fa[205][205];
pair<int,int> find(int x,int y){
	if (fa[x][y]==(pair<int,int>){x,y})return {x,y};
	else return fa[x][y]=find(fa[x][y].first,fa[x][y].second);
}
void merge(int x,int y,int X,int Y){
	pair<int,int> temp=find(x,y);
	x=temp.first,y=temp.second;
	temp=find(X,Y);
	X=temp.first,Y=temp.second;
	fa[X][Y]={x,y};
}
int check(int x,int y,int X,int Y){
	pair<int,int> temp=find(x,y);
	x=temp.first,y=temp.second;
	temp=find(X,Y);
	X=temp.first,Y=temp.second;
	return x==X&&y==Y;
}
void solve(){
	cin>>n>>m>>k;
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			cin>>c[i][j];
			fa[i][j]={i,j};
		}
	}
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			if (i!=n-1){
				if (c[i][j]=='.'||c[i+1][j]=='.'||c[i][j]==c[i+1][j]){
					merge(i,j,i+1,j);
				}
			}
			if (j!=m-1){
				if (c[i][j]=='.'||c[i][j+1]=='.'||c[i][j]==c[i][j+1]){
					merge(i,j,i,j+1);
				}
			}
		}
	}
	while (k--){
	    int x,y,X,Y;cin>>x>>y>>X>>Y; 
	    if (check(x,y,X,Y))cout<<"YES\n";
	    else cout<<"NO\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while (t--)solve();
}
