// Source: https://usaco.guide/general/io
//alvin yu

#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
	int t;
	cin >> t;

	while (t--){
		int n, r;
		cin >> n >> r;

		vector<int> nums(n);
		for (int i = 0; i < n; i++) cin >> nums[i];

		bool works = true;
		int smoke1 = r, smoke2 = 0;
		for (int i = 1; i < n; i++){
			int time = nums[i] - nums[i - 1];
			if (smoke1 == 0) smoke2 = max(smoke2 - time, (long long) 0);
			else if (time > smoke1) {
				smoke2 = max(smoke2 - time + smoke1, (long long) 0);
				smoke1 = 0;
			} else smoke1 -= time;

			if (smoke1 == 0) {
				smoke1 = smoke2;
				smoke2 = r;
			} else works = false;
		}

		cout << (works ? "YES\n" : "NO\n");
	}
}
