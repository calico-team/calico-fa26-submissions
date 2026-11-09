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
string solve(int N, int R, const vector<long long>& A) {
	int curr = R;
	for (int i = 0; i < N-1; i++) {
		int dt = A[i+1] - A[i];
		curr = min(curr + dt, 2*R);
		curr -= R;
		if (curr < 0) {
			return "NO";
		}
	}
	return "YES";
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	//freopen("00_main.in", "r", stdin);
	int T; cin >> T;
	while (T--) {
		long long N, R; cin >> N >> R;
		vector<long long> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}