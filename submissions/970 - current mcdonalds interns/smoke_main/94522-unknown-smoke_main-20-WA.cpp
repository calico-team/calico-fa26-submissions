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
		int t1,t2;
		t1 = req[0]+r;
		t2 = req[0]+2*r;
		bool ans = true;
		for (int i=0;i<n&&ans==true;i++){
			if (req[i]>t1) {
				charges++;
				if (req[i]>t2) charges++;
				t1 = req[i]+r;
				t2 = req[i]+2*r;
			}
			charges = charges>2?2:charges;
			if (charges < 1){
				ans = false;
				break;
			}
			else charges--;
		}
		cout << (ans?"Yes":"No") << '\n';
	}
}
