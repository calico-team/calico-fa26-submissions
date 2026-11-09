#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> e[1000005];
int f[1000005];
void dfs(int u){
	for (int v:e[u]){
		if (v==f[u])continue;
		f[v]=u;dfs(v);
	}
}
void solveF(){
	int n;
	cin>>n;
	int res=0;
	for (int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		res^=(u+v);
	}
	dfs(1);
	cout<<res<<" ";
	for (int i=2;i<=n;i++){
		cout<<f[i]<<" ";
	}
	cout<<"\n";
}
int a[1000005];
void solveS(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)cin>>a[i];
	if (a[1]==-1){
		for (int i=2;i<=n;i++){
			cout<<i<<" "<<a[i]<<"\n";
		}
	}
	else{
		int p;
		for (int i=2;i<=n;i++){
			if (a[i]!=-1)a[1]^=(i+a[i]);
			else p=i;
		}
		a[p]=a[1]-p;
		for (int i=2;i<=n;i++){
			cout<<i<<" "<<a[i]<<"\n";
		}
	}
}
void solve(){
	string s;
	cin>>s;
	if (s[0]=='F')solveF();
	else solveS(); 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t=1;//cin>>t;
	while (t--)solve();
}
