#include<iostream>
#include<algorithm>

using namespace std;

constexpr int N=1e5+5;

#define int long long 

int n,r,a[N];
int have,pass;

namespace tqy{
	inline void init(){
		cin>>n>>r;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		have=2;
	}
	inline void solve(){
		have=1;
		pass=0;
		for(int i=2;i<=n;++i){
			int dlt=a[i]-a[i-1]+pass;
			int more=dlt/r;
			have+=more;
			if(have>=2){
				have=2;
				pass=0;
			}else{
				pass=dlt%r;
			}
			--have;
			if(have<0){
				cout<<"NO\n";
				return;
			}
		}
		cout<<"YES\n";
	}
}

signed main(){
	int T;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--)tqy::init(),tqy::solve();
	return 0;
}