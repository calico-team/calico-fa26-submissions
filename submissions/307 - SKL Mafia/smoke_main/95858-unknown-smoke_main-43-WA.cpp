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
	// YOUR CODE HERE
	bool canDoIt = true;
	int charges = 2;
	int last = 0;
	for (int t: A) {
		if (charges >= 1) {
		    if (charges == 1 && t - last > R) {
		        charges++;
		        last = t;
		    }
			charges--;
			continue;
		} else {
			if (t - last >= R) {
				if (t - last > R*2) charges++;
				last = t;
				continue;
			} else {
				canDoIt = false;
				last = t;
				break;
			}
		}
	}
	return canDoIt ? "YES" : "NO";
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
