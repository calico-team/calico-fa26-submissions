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
	int cumulative = 0;
	for (int i = 0; i < N-1; i++) {
		int b = A[i+1] - A[i] - R;
		if (cumulative < -7) {
			return "NO";
		}
		cumulative = min(0, cumulative + b);
	}
	return "YES";
}

int main() {
	//freopen("00_main.in", "r", stdin);
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
