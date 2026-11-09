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
// EVOLVE-BLOCK-START
string solve(int N, int R, vector<int> A) {
        int availableCharges = 2;
        int rechargingIndex = -1;

        for (int i = 0; i < N; ++i) {
            if (i == rechargingIndex) {
                availableCharges = 2;
                rechargingIndex = -1;
            } else if (availableCharges == 0) {
                return "NO";
            }

            if (i + R < A[i]) {
                rechargingIndex = i + R;
            }

            --availableCharges;
        }

        return "YES";
    }
// EVOLVE-BLOCK-END

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