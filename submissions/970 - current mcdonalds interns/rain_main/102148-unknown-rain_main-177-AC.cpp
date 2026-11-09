#include <bits/stdc++.h>
#define int long long
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

signed main(){
	fast;
	int t; cin >> t;
	while (t--){
		int n, k;
		cin >> n >> k;
		vector<vector<int>> east, north;
		for (int i = 0; i < n; i++){
			vector<int> drone(3);
			char direction;
			cin >> drone[0] >> drone[1] >> drone[2] >> direction;
			if (direction == 'N') north.push_back(drone);
			if (direction == 'E') east.push_back(drone);
		}

		const int MAXS = 200005;
		vector<vector<vector<int>>> groupsN(MAXS), groupsE(MAXS);
		for (auto &d : north) groupsN[d[0] + d[1]].push_back(d);
		for (auto &d : east ) groupsE[d[0] + d[1]].push_back(d);

		for (auto &g : groupsE)
			sort(g.begin(), g.end(),
			 [](const vector<int>& a, const vector<int>& b){
				 return a[0] < b[0];
			 });

		int ans = n * k;
		for (int i = 0; i < MAXS; i++){
			for (auto &drone : groupsN[i]){
				auto upper = upper_bound(
					groupsE[i].begin(), groupsE[i].end(), drone[0],
					[](int v, const vector<int>& a){ return v < a[0]; });
				auto lower = upper_bound(
					groupsE[i].begin(), groupsE[i].end(), drone[0] - k,
					[](int v, const vector<int>& a){ return v < a[0]; });
				ans -= distance(lower, upper);
			}
		}
		cout << ans << '\n';
	}
}
