#include <iostream>
#include <vector>
using namespace std;
#define int long long

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
	int first = 0;
	int second = 0;
	for (int i = 0; i < N; i++) {
		int smokereq = A[i];
		if (smokereq < first) {
			return "NO";
		}
		int charge;
		if (smokereq > second) {
			charge = smokereq;
		}
		else {
			charge = second;
		}
		int used = charge + R;
		first = second;
		second = used;
	}
	return "YES";
}
signed main() {
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
