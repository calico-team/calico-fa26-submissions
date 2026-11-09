#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
template<typename T> using oset = 
__gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, 
__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<typename T> using rpriority_queue =
priority_queue<T, vector<T>, greater<T>>;
#define ckmin(x, y) x=min(x, y)
#define ckmax(x, y) x=max(x, y)
#define vt vector
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ll long long
#define ull unsigned ll
#define ld long double
#define okey order_of_key
#define oget find_by_order
#define lg(x) (int)log2(x)
#define MP make_pair
#define breakpoint cout<<"works\n";return;
typedef vt<int> vi;
typedef pair<int,int> pi;
typedef pair<ll, ll> pll;
typedef vt<vt<ll>> mat;
const ll MAXN = 2e5+3;
const ll MAXM = 2e5+4;
const ll MAXL = 1e15+3;
const ll INF = 1000000000;
const ll MOD = 1e9+9;
const double PI = 3.14159;
ll N, K;
void solve(){
	cin>>N>>K;
	set<pair<ll, pll>> ps;
	for(int i = 0; i<N; ++i){
		ll x, y, z, d;
		cin>>x>>y>>z;
		string s;
		cin>>s;
		d = (s == "N");
		ps.insert(MP(x, MP(y, d)));
	}
		
	map<ll, rpriority_queue<ll>> pqs[2];
	ll sum = 1LL*sz(ps)*K;
	for(auto p : ps){
		ll x = p.first, y = p.second.first, d = p.second.second;
		ll diff = x-y;
		for(int j = 0; j<2; ++j){
			while(!pqs[1-d][diff].empty()){
				ll x1 = pqs[1-d][diff].top();
				//cout<<x1<<" here\n";
				if(x-x1+1 <= K) break;
				pqs[1-d][diff].pop();
			}
			//cerr<<sz(pqs[1-d][diff])<<" "<<x<<" "<<y<<"\n";
			sum -= d*1LL*sz(pqs[1-d][diff]);
			pqs[d][diff].push(x);
			diff = x+y;
			if(diff == x-y) continue;
		}
	}
	
	cout<<sum<<"\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t = 1;
	cin>>t;
	while(t--) solve();
} 	