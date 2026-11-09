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
const ll MOD = 1e9+9;
const ll B = 9973;
const ll INV = 637621584;
const ll INF = INT32_MAX;
int N, R, a[MAXN];
void solve(){
	cin>>N>>R;
	for(int i = 0; i<N; ++i){
		cin>>a[i];
	}
	
	int cnt = 2, prev = 0;
	for(int i = 0; i<N; ++i){
		if(a[i]-prev >= R){
			cnt = min(2, cnt+1);
			prev = a[i];
		}
		
		if(cnt-- == 0){
			cout<<"NO\n";
			return;
		}
		
		if(cnt > 0) prev = a[i];
	}
	
	cout<<"YES\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t = 1;
	cin>>t;
	while(t--) solve();
} 	