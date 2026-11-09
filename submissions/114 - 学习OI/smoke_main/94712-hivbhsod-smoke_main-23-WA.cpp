#ifdef LOCAL
#define sc cerr
#else
#define sc if(0)cerr
#pragma GCC optimize("O2")
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

bool solve(){
	int n,m; cin>>n>>m;
	vector<int> a(n);
	for(int &x:a)cin>>x;

	int cur=2;
	rep(i,0,n-1){
		cur--;
		if(i>0 && a[i]-a[i-1]>=m){cur++;}
		if(i>0 && a[i]-a[i-1]>=2*m){cur++;}
		cur=min(cur,2);
		if(cur<0){ return 0; }
	}
	return 1;
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin>>T;
	while(T--)puts(solve()?"YES":"NO");
}
