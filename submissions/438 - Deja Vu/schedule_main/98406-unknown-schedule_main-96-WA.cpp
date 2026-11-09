#include "bits/stdc++.h"
using namespace std;
#define mod 1000000007
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define N 24
#define maxn 200005
#define INF (int)1e9

int n,m,k,ans=0;
bool b[maxn],d[maxn],used[maxn];
vector<int> v[maxn];

int check(){
	int mx=-1,cur=-1;
	for(int i=1; i<=n; i++){
		if(!b[i] or used[i])continue;
		int cnt=0;
		for(auto u:v[i]){
			if(!(b[u]|d[u]))cnt++;
		}
		if(cnt>mx)mx=cnt,cur=i;
	}
	if(cur==-1)return -1;
	used[cur]=true;
	ans++;
	for(auto u:v[cur]){
		d[u]=true;
	}
	return 0;
}

void solve(){
	cin>>n>>m>>k;
	int pr[maxn];
	for(int i=1; i<=n; i++){
		cin>>pr[i];
		if(pr[i]!=0)v[pr[i]].pb(i);
		else b[i]=true;
	}
	for(int i=1; i<=m; i++){
		if(ans==n)break;
		for(int j=1; j<=k; j++){
			if(check()==-1)break;
		}
		for(int j=1; j<=n; j++)b[j]=(b[j]|d[j]),d[j]=false;
	}
	cout<<ans<<'\n';
	ans=0;
	for(int i=1; i<=n; i++)b[i]=d[i]=used[i]=0,v[i].clear();
}
 
int main(){
	// freopen("in.txt","w",stdout);
	// freopen("out.txt","r",stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t=1;
	cin>>t;
	while(t--) solve();
}