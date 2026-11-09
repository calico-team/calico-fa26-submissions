#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main (){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t; cin >> t;
	while (t--){
		int n, r; cin >> n >> r; //n requests, r recharge time
		vector <int> req(n); 
		for (int i = 0; i < n; i++){
			cin >> req[i];
		}
		
		bool possible = true;
		int a = 0, b = 0;
		
		for (int i = 0; i < n; i++){
			if (req[i] >= a){
				int temp = b;
				b = max(req[i], b)+r;
				a = temp;
			} else{
				possible = false;
			}
		}
		
		if (possible) cout << "YES" << '\n';
		else cout << "NO" << '\n';
	}
	
	
	return 0;
}
