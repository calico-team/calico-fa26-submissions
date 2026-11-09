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
    bool able = true;
    vector<int> recharge(N);
    recharge[0] = A[0] + R;
    for (int i = 1; i < N; i++) {
        recharge[i] = max(A[i], recharge[i-1]) + R;
        if (i >= 2) {
            if (recharge[i-2] > A[i]) {
                able = false;
                break;
            }
        }
    }

    if (able) return "YES";
	return "NO";
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
