#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

#define endl "\n"

struct drone {
	long long x;
	long long y;
	long long z;
	long long dir;
	long long cross;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	long long t;
	cin >> t;

	for (long long ab = 0; ab < t; ab++) {
		long long n, k;
		cin >> n >> k;

		map<long long, vector<long long>> east, north;

		vector<drone> drones(n);
		for (long long x = 0; x < n; x++) {
			drone dron;
			cin >> dron.x >> dron.y >> dron.z;
			char a;
			cin >> a;
			if (a == 'N') dron.dir = 1;
			else dron.dir = 0;
			dron.cross = dron.x + dron.y;
			drones[x] = dron;

			if (dron.dir == 0) east[dron.cross].push_back(dron.x);
			else north[dron.cross].push_back(dron.y);
		}

		for (auto &it : east) {
			sort(it.second.begin(), it.second.end());
		}


		long long total = n * k;


		for (long long x = 0; x < n; x++) {
			if (drones[x].dir == 1) {
				auto l = lower_bound(east[drones[x].cross].begin(), east[drones[x].cross].end(),drones[x].x-k+1);
				auto r = upper_bound(east[drones[x].cross].begin(), east[drones[x].cross].end(), drones[x].x);
				total -= (r - l);
			}
		}
		cout << total << endl;
		

	}
}