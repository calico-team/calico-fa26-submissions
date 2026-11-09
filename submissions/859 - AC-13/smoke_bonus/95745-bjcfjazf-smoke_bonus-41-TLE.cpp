#include <iostream>
#include <queue>
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
    int charges = 2;
    int t1 = -1, t2 = -1;

    for (int i = 0; i < N; i++) {
        int time = A[i];

        if (t1 != -1 && t1 <= time) {
            charges++;
            t1 = t2;
            t2 = -1;
        }
        if (t1 != -1 && t1 <= time) {
            charges++;
            t1 = t2;
            t2 = -1;
        }
        if (charges > 2) charges = 2;

        if (charges == 0) {
            return "NO";
        }

        charges--;

        if (t1 == -1) {
            t1 = time + R;
        } else {
            t2 = t1 + R;
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
