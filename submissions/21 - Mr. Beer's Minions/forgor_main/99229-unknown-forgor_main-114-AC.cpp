#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pb push_back
#define debug(x) cerr<<#x<<"="<<x<<endl
#define inf (1ll<<60) // Wrapped in parentheses for safety
#define rep(i,a,b) for (ll i=a;i<(b);i++)
#define MP make_pair
#define mod (ll)998244353
#define SZ(x) (int(x.size()))
#define ALL(x) x.begin(),x.end()
#define endl "\n" //comment out for interactives
ll lowbit(ll x) {return x&(-x);}

const ll maxn = 2e5+5;
vector<ll>alist[maxn];
ll par[maxn],ans[maxn];

void dfs(ll u,ll p){
	par[u] = p;
	for(auto x:alist[u]){
		if(x==p)continue;
		dfs(x,u);
	}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;cin>>s;
    ll n;cin>>n;
    if(s=="FIRST"){
		rep(i,0,n-1){
			ll a,b;cin>>a>>b;
			alist[a].pb(b);
			alist[b].pb(a);
		}
		dfs(1,-1);
		ll zor = 0;
		rep(i,2,n+1){
			ans[i] = par[i]; //node 1 is the root
			zor ^= par[i];
		}
		ans[1] = zor;
		rep(i,1,n+1)cout<<ans[i]<<" ";
		cout<<endl;
	}else{
		ll id = -1,zor=0;
		rep(i,1,n+1){
			cin>>ans[i];
			if(ans[i]==-1)id = i;
			else zor^=ans[i];
		}
		ans[id]=zor;
		rep(i,2,n+1)cout<<i<<" "<<ans[i]<<endl;
	}
    return 0;
}


