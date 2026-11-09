#include<bits/stdc++.h>
using namespace std;
#define int long long

int fa[200010],dep[200010],sz[200010],n,m,k,dp[100010];
vector<int>g[200010];

void dfsd(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dep[v]=dep[u]+1;
		dfsd(v);
	}
}

void dfsz(int u){
	sz[u]=1;
	if(dep[u]==m) return;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dfsz(v);
		sz[u]+=sz[v];
	}
}

void dfsdp(int u){
	dp[u]=1;
	int sum=0;
	priority_queue<int,vector<int>,greater<int> >pq;
	if(dep[u]==m){
		return;
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dfsdp(v);
		if(pq.size()<k) pq.push(dp[v]),sum+=dp[v];
		else{
			if(pq.top()<dp[v]) sum-=pq.top(),pq.pop(),sum+=dp[v],pq.push(dp[v]);
		}
	}
	dp[u]+=sum;
}

signed main(){
	int t;
	cin>>t;
	while(t--){
		memset(dp,0,sizeof(dp));
		for(int i=0;i<=n;i++) g[i].clear();
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			cin>>fa[i];
			g[fa[i]].push_back(i);
		}
		dfsd(0);
		dfsz(0);
		dfsdp(0);
		cout<<dp[0]-1<<endl;
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
