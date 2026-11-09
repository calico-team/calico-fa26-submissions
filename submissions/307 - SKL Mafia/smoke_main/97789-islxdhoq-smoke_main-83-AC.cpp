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
    long long avail1 = 0, avail2 = 0;
   
    for (long long t : A) {
        if (avail1 <= t || avail2 <= t) {
            if (avail1 <= avail2) {
                if (avail1 <= t) {
                    avail1 = max(t, avail2) + R;
                } else {
                    return "NO";
                }
            } else {
                if (avail2 <= t) {
                    avail2 = max(t, avail1) + R;
                } else {
                    return "NO";
                }
            }
        } else {
            return "NO";
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
