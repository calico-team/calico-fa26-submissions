#include <bits/stdc++.h>
using namespace std;

struct drone {
	int x;
	int y;
	int cx = 0;
	int cy = 0;
};
int bins(vector<int> &v, int tar) {
	int l = 0, r = v.size();
	
	while (l < r) {
		int mid = (l + r) / 2;
		
		if (v[mid] < tar) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
	
	return l;
}
int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		long long tot = 0;
		int n, k;
		cin >> n >> k;
		drone drones[100000];
		
		vector<int> mp[200001];
		
		for (int j = 0; j < n; j++) {
			int x, y, z;
			char dir;
			cin >> x >> y >> z >> dir;
			drones[j].x = x;
			drones[j].y = y;
			if (dir == 'N') drones[j].cy = 1;
			if (dir == 'E') {
				drones[j].cx = 1;
				mp[x + y].push_back(x); 
			}
			
			tot += k;
		}
		
		for (int j = 0; j <= 200000; j++) {
			sort(mp[j].begin(), mp[j].end());
		}
		
		for (int j = 0; j < n; j++) {
			if (drones[j].cx == 1) continue;
			int x = drones[j].x;
			int y = drones[j].y;
			vector<int> &v = mp[x+y];
			int l = bins(v,x-k+1);
			int r = bins(v,x);
			
			tot-=r-l;
		}
		
		cout << tot << '\n';
	}
	return 0;
}

