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
	long long charges = 2, nxt = 0; // nxt: time the in-progress recharge finishes
	for (int i = 0; i < N; i++) {
		long long a = A[i];
		while (charges < 2 && nxt <= a) {
			charges++;
			if (charges < 2) nxt += R; // next recharge starts when previous finishes
		}
		if (charges == 0) return "NO";
		if (charges == 2) nxt = a + R; // recharge starts now
		charges--;
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
