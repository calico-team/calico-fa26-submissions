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
	return "NO";
}

int main() {
	int T; cin >> T;
    bool able = true;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<int> A(N);
        vector<int> recharge(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
            recharge[0] = A[0] + R;

            if (i >= 1) {
                recharge[i] = max(A[i], recharge[i-1]) + R;
                if (i >= 2) {
                    if (recharge[i-2] > A[i]) {
                        able = false;
                    }
                }
            }
		}
        if (able) cout << "YES" << "\n";
        else cout << "NO" << "\n";
	}
}
