#include <iostream>
#include <vector>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
	int currentUses = 2;
	int currentTime = 0;
	int lastDiff = 0;

	for (int i = 0; i < N; i++) {
		currentUses = min(2, currentUses + (A[i] - currentTime + lastDiff) / R);
		lastDiff = (A[i] - currentTime + lastDiff) % R;
		currentTime = A[i];

		if (currentUses == 2) {
			lastDiff = 0;
		}

		currentUses--;
		if (currentUses < 0) {
			return "NO";
		}
	}

	return "YES";
}

int main() {
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
