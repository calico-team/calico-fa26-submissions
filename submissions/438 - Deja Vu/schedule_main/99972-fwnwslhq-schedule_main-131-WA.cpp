#include "bits/stdc++.h"
using namespace std;
#define mod 1000000007
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define N 24
#define maxn 200005
#define INF (ll)1e9

ll ans=0;
bool b[maxn],d[maxn],used[maxn];
vector<ll> v[maxn];

ll check(ll n){
	ll mx=-1,cur=-1;
	for(ll i=1; i<=n; i++){
		if(!b[i] or used[i])continue;
		ll cnt=0;
		for(ll j=0; j<v[i].size(); j++){
			if(!(b[v[i][j]]|d[v[i][j]]))cnt++;
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
	ll n,m,k;
	cin>>n>>m>>k;
	for(ll i=1; i<=n; i++){
		ll x;
		cin>>x;
		if(x!=0)v[x].pb(i);
		else b[i]=true;
	}
	for(ll i=1; i<=m; i++){
		if(ans==n)break;
		for(ll j=1; j<=k; j++){
			if(check(n)==-1)break;
		}
		for(ll j=1; j<=n; j++)b[j]=(b[j]|d[j]),d[j]=false;
	}
	cout<<ans<<'\n';
	ans=0;
	for(ll i=1; i<=n; i++)b[i]=d[i]=used[i]=0,v[i].clear();
}
 
int main(){
	// freopen("in.txt","w",stdout);
	// freopen("out.txt","r",stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t=1;
	cin>>t;
	while(t--) solve();
}