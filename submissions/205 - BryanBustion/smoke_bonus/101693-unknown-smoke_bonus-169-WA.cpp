#include <bits/stdc++.h>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
    int charges = 2;
    int nextRecharge = -1;
    for (int i = 0; i < N; i++) {
        if (nextRecharge != -1 && A[i] >= nextRecharge) {
            charges++;
            nextRecharge = -1;
        }
        if (charges == 0) {
            return "NO";
        }
        charges--;
        if (nextRecharge == -1) {
            nextRecharge = A[i] + R;
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