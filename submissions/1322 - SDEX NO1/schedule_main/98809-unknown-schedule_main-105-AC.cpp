#include <bits/stdc++.h>
using namespace std;
const int MAXM=50005+2000;
vector<int> p;
vector<vector<int> > adj;
vector<int> d;
bool cmp(int a,int b){
	return a<b;
}
void dfs(int u,int dep){
	int i;
	d[u]=dep;
	for(i=0;i<adj[u].size();++i){
		int v=adj[u][i];
		dfs(v,dep+1);
	}
}
int find(int x){
	if(p[x]!=x)
		p[x]=find(p[x]);
	return p[x];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	int T;
	cin>>T;
	while(T--){
		int n,m,k;
		cin>>n>>m>>k;
		vector<int> P(n+1);
		adj.assign(n+1,vector<int>());
		int i;
		for(i=1;i<=n;++i){
			cin>>P[i];
			if(P[i]!=0){
				adj[P[i]].push_back(i);
			}
		}
		d.assign(n+1,0);
		for(i=1;i<=n;++i){
			if(P[i]==0){
				dfs(i,1);
			}
		}
		vector<int> courses(n);
		for(i=0;i<n;++i){
			courses[i]=i+1;
		}
		sort(courses.begin(),courses.end(),cmp);
		p.resize(m+1005);
		for(i=0;i<=m+1000;++i){
			p[i]=i;
		}
		int ans=0;
		vector<int> cap(m+1005,0);
		for(i=0;i<courses.size();++i){
			int id=courses[i];
			int t0=d[id];
			int t=find(t0);
			if(t>m)
				continue;
			ans++;
			cap[t]++;
			if(cap[t]==k){
				p[t]=find(t+1);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}

