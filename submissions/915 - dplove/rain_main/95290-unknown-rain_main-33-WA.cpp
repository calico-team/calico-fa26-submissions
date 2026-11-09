#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, K;
	cin >> N >> K;

	map<int, vector<int>> diagonals;
	vector<pair<int, int>> north;

	for (int i = 0; i < N; i++) {
		int X, Y, Z;
		char D;
		cin >> X >> Y >> Z >> D;

		if (D == 'E') {
			diagonals[X + Y].push_back(Y);
		} else {
			north.push_back({X, Y});
		}
	}

	for (auto& [sum, rows] : diagonals) sort(rows.begin(), rows.end());

	int meetings = 0;
	for (auto [x, y] : north) {
		if (!diagonals.count(x + y)) continue;

		vector<int>& rows = diagonals[x + y];

		int first = upper_bound(rows.begin(), rows.end(), y) - rows.begin();
		int last = upper_bound(rows.begin(), rows.end(), y + K - 1) - rows.begin();

		meetings += last - first;
	}

	cout << N * K - meetings << "\n";
}
