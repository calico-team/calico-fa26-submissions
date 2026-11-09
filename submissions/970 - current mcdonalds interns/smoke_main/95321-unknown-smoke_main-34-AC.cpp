#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int t; cin >> t;
	while (t--){
		int n,r;
		cin >> n >> r;
		vector<int> req(n);
		for (int i=0;i<n;i++) cin >> req[i];
		int charges = 2;
		int recharge = req[0] + r;
		bool ans = true;
		for (int i=0;i<n;i++){
			while (req[i]>=recharge && charges<2){
				charges++;
				recharge += r;
			}
			if (charges == 2) recharge = req[i]+r;
			if (charges < 1){
				ans = false;
				break;
			}
			else charges--;
		}
		cout << (ans?"Yes":"No") << '\n';
	}
}
