// Source: https://usaco.guide/general/io
//alvin yu

#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(nullptr); 
	int t;
	cin >> t;

	while (t--){
		int n, r;
		cin >> n >> r;

		vector<int> nums(n);
		for (int i = 0; i < n; i++) cin >> nums[i];

		bool works = true;
		int cd = r;
		for (int i = 1; i < n; i++){
			cd = max(cd - nums[i] + nums[i - 1], (long long) 0);
			if (cd <= r) cd += r;
			else works = false;
		}
		cout << (works ? "YES\n" : "NO\n");
	}
}
