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


const ll maxn = 1e5+5;
ll a[maxn];

void solve(){
    ll n,r;cin>>n>>r;
    ll cd1 = 0, cd2 = 0;
    rep(i,1,n+1)cin>>a[i];
    rep(i,1,n+1){
		if(cd1>a[i]){
			cout<<"NO"<<endl;
			return;
		}
		ll nxt = max(a[i],cd2)+r;
		cd1 = cd2;
		cd2 = nxt;
	}
	cout<<"YES"<<endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll _;cin>>_;
    while(_--)solve();
    return 0;
}


