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
ll N, M, Q, sz[MAXN], pt[MAXN];
ll find(ll x){
	while(pt[x] != x) x = pt[x];
	return x;
}
bool same(ll x, ll y){
	return (find(x) == find(y));
}
void unite(ll x, ll y){
	if(same(x, y)) return;
	
	x = find(x); y = find(y);
	if(sz[x] < sz[y]) swap(x, y);
	ckmax(sz[x], sz[y]+1);
	pt[y] = x;
}
void init(){
	iota(pt, pt+N*M+1, 0);
	fill(sz, sz+N, 0LL);
}
void solve(){
	cin>>N>>M>>Q;
	init();
	
	string s[N];
	for(int i = 0; i<N; ++i){
		cin>>s[i];
	}
	
	map<char, int> m;
	m['B'] = -1;
	m['.'] = 0;
	m['R'] = 1;
	for(int i = 0; i<N; ++i){
		for(int j = 0; j<M; ++j){
			for(int x = -1; x<2; ++x){
				for(int y = -1; y<2; ++y){
					if(abs(x) == abs(y)) continue;
					if(x+i >= N || x+i < 0 || y+j >= M || y+j < 0) continue;
					if(abs(m[s[i][j]] - m[s[x+i][y+j]]) == 2) continue;
					
					
					unite(i*M+j, M*(x+i) + (y+j));
				}
			}
		}
	} 
	
	//cout<<same(5, 6)<<"\n";
		
	while(Q--){
		int xc, yc, xe, ye;
		cin>>xc>>yc>>xe>>ye;
		//++xc; ++yc; ++xe; ++ye;
		
		if(same(M*xc + yc, M*xe + ye)) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t = 1;
	cin>>t;
	while(t--) solve();
} 	