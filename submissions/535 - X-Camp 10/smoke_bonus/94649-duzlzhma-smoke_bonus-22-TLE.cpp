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
	int last = A[N-1];
	vector<bool> smokereq(last + 1, false);
	for (int i = 0; i < N; i++) {
		smokereq[A[i]] = true;
	}
	int smokes = 2;
	int timer = 0;
	for (int i = 1; i <= last; i++) {
		if (smokes < 2) {
			timer--;
			if (timer == 0) {
				smokes++;
				if (smokes < 2) {
					timer = R;
				}
			}
		}
		if (smokereq[i]) {
			if (smokes == 0) {
				return "NO";
			}
			if (smokes == 2) {
				timer = R;
			}
			smokes--;
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
