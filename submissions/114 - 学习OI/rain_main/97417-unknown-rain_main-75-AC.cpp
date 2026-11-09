#ifdef LOCAL
#define sc cerr
#else
#define sc if(0)cerr
//#pragma GCC optimize("O2")
#endif

#include<bits/stdc++.h>
//#include<bits/extc++.h>

#define qlog(x) {sc<<#x<<" = "<<(x)<<"\n";}
#define rep(i,l,r) for(int i=(l);i<=(r);i++) 
#define irep(i,r,l) for(int i=(r);i>=(l);i--) 
#define qloga(a,l,r) {sc<<#a<<": "; rep(I,(l),(r)){sc<<a[I]<<" ";}sc<<"\n";}
#define qlogSTL(a) {sc<<#a<<": "; for(const auto &I:(a)){sc<<I<<" ";}sc<<"\n";}
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//typedef __int128 i128;

constexpr int N=2e5+10;
int n,m;
vector<pair<int,int>> q[N];

int bit[N];
vector<int> stk;

int ok[N];
void add(int i,int x){
	i++;
	ok[i]+=x;
	stk.push_back(i);
	for(;i<N;i+=(i&-i)){
		bit[i]+=x;
	}
}
void clear(){
	for(int i:stk)for(;i<N;i+=(i&-i)){
		bit[i]=0;
	}
	for(int i:stk)ok[i]=0;
	stk.clear();
}
int query(int r){
	r++;
	int ans=0;
	for(int i=r;i;i-=(i&-i)){
		ans+=bit[i];
	}
	return ans;
}

ll solve(){
	cin>>n>>m;
	set<ll> mp;
	ll ans=1LL*n*m;
	rep(i,1,n){
		int x,y,z;
		cin>>x>>y>>z;
		char d; cin>>d;
		if(mp.count(x*1000000000LL+y)){
			ans-=m;
			continue;
		}
		mp.insert(x*1000000000LL+y);
		if(d=='E'){
			q[x+y].push_back({x,0});
		}else{
			q[x+y].push_back({x,1});
		}
	}

	m--;
	rep(v,0,N-1)if(q[v].size()){
		auto &a=q[v];
		sort(a.begin(),a.end());
		int w=a.size();

		int l=0,sum=0;
		rep(r,0,w-1){
			sum+=!a[r].second;
			while(l<r && a[r].first-a[l].first>m){
				sum-=!a[l].second;
				l++;
			}
			if(a[r].second)ans-=sum;
		}

		q[v].clear();
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0);

	int T; cin>>T;
	while(T--)cout<<solve()<<"\n";
}
