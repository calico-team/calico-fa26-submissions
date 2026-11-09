#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int N, R;
		cin >> N >> R;

		vector<int> A(N, 0);
		for (int i = 0; i < N; i++) cin >> A[i];

		sort(A.begin(), A.end());

		int charges = 2, readyAt = 0;
		bool possible = true;

		for (int i = 0; i < N; i++) {
			while (charges < 2 && readyAt <= A[i]) {
				charges++;
				if (charges < 2) readyAt += R;
			}

			if (charges == 0) {
				possible = false;
				break;
			}

			if (charges == 2) readyAt = A[i] + R;
			charges--;
		}

		if (possible) {
			cout << "YES" << "\n";
		} else {
			cout << "NO" << "\n";
		}
	}
}
