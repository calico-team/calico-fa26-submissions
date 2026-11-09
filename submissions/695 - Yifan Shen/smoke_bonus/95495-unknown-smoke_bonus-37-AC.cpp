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
string solve(int N, int R, vector<int> &A) {
	// YOUR CODE HERE

	long long s1 = 0;
	long long s2 = 0;

	for (int i = 0; i < N; i++) {

		long long a = A[i];

		if (s1 > a) {

			return "NO";

		}

		s1 = s2;
		s2 = max(a, s2) + R;

	}

	return "YES";

}

int main() {

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
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
