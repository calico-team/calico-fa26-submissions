#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k;
	cin >> n >> k;
	map<int, array<vector<int>, 2>> drones;
	for (int i = 0; i < n; i++) {
		int x, y, z;
		char d;
		cin >> x >> y >> z >> d;
		drones[x + y][d == 'N'].push_back(x);
	}
	int64_t rainwater = k * 1LL * n;
	for (auto &[_, vs] : drones) {
		auto &[E, N] = vs;
		// cerr << _ << " : " << E.size() << "E, " << N.size() << "N\n";
		sort(E.begin(), E.end());
		sort(N.begin(), N.end());
		for (int xE : E) {
			rainwater -= lower_bound(N.begin(), N.end(), k + xE) - lower_bound(N.begin(), N.end(), xE);
		}
	}
	cout << rainwater << '\n';
	// cerr << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}
// E: x, y -> x + k, y
// N: x, y -> x, y + k
// N interval: [y, y + k] na x
// 1=N, 2=E
// se secat samo N i E max ednas, koga yN + t = yE, x1 = x2 + t, t <= k
// t = y2 - y1 = x1 - x2
// x1 + y1 = x2 + y2
// 0 < x1 - x2 <= k
// xE < xN <= k + xE