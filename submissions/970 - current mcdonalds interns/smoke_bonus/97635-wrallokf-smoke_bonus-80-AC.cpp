#include <bits/stdc++.h>
#define int long long
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
signed main(){
    fast;
	int t; cin>>t;
	while (t--) {
		int n, r; cin>>n>>r;
		int charges = 2;
		int recharge = 0;
		bool ans = 1;
		for (int i=0;i<n;i++){
			int req; cin>>req;
			if (!ans) continue;
			if (i == 0) recharge = req+r;
			while (req>=recharge && charges<2){
				charges++;
				recharge += r;
			}
			if (charges == 2) recharge = req+r;
			if (charges < 1){
				ans = false;
			}
			else charges--;
		}
		cout<<(ans?"YES":"NO")<<'\n';
	}
}
