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

// (xi + t, yi) = (xj, yj + t) => xj + yj = xi + yi
void solve(){
	ll n,k;cin>>n>>k;
	map<ll,vector<ll>>east,north;
	rep(i,1,n+1){
		ll x,y,z;
		char d;
		cin>>x>>y>>z>>d;
		if(d == 'N')north[x+y].pb(x);
		if(d == 'E')east[x+y].pb(x);
	}
	ll ans = n*k;
	for(auto [w,ex]:east){
		if(north[w].empty())continue;
		vector<ll>nx = north[w];
		sort(ALL(ex));
		sort(ALL(nx));
		ll p = 0, pp = 0;
		for(auto xx:ex){ //any north element with east x val in [x+1,x+k-1] should be ok
			while(p < SZ(nx) and nx[p] < xx+1)p++;
			while(pp < SZ(nx) and nx[pp] <= xx+k-1)pp++;
			ans -= (pp-p);
		}
	}
	cout<<ans<<endl;
	
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll _;cin>>_;
    while(_--)solve();
    return 0;
}


