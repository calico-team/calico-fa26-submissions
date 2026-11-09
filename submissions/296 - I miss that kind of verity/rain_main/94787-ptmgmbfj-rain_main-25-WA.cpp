#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		// store [x + y] = [pts] for north and east
		// only consider points in the same [x+y]
		// for E-N, consider x values in [x, x+k-1]

		int n, k;
		cin >> n >> k;
		ll ans = ll(n) * k;
		set<pii> seenEast, seenNorth;
		map<int, vector<int>> east;
		map<int, vector<int>> north;
		for (int i = 0; i < n; i++) {
			int x, y, z;
			char dir;
			cin >> x >> y >> z >> dir;
			pii key {x, y};
			if (dir == 'N') {
				if (!seenNorth.insert(key).second) {
					ans -= k;
					continue;
				}
				north[x+y].push_back(x);
			}
			else {
				if (!seenEast.insert(key).second) {
					ans -= k;
					continue;
				}
				east[x+y].push_back(x);
			}
		}

		for (const auto& [xy, eastVec] : east) {
			auto it = north.find(xy);
			if (it == north.end()) continue;
			const auto& northVec = it->second;
			int northLen = northVec.size(), eastLen = eastVec.size();
			for (int i = 0, j = 0, start = 0; i < eastLen; i++) {
				while (j < northLen && northVec[j] - eastVec[i] < k) j++;
				while (start < j && northVec[start] < eastVec[i]) start++;
				ans -= j - start;
			}
		}

		cout << ans << '\n';
	}
}
