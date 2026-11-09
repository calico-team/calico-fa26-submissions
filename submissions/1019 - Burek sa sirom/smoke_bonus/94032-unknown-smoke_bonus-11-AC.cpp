#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, r, t;
	bool good = true;
	cin >> n >> r >> t;
	int bar = r;
	for (int i = 1, T; i < n; i++) {
		cin >> T;
		bar = min(bar + T - t, r << 1);
		if (bar < r) good = false;
		bar -= r;
		t = T;
		// cerr << "T=" << T << ", " << "bar=" << bar << '\n';
	}
	cout << (good ? "YES\n" : "NO\n");
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}