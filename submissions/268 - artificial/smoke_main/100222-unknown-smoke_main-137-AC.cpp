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
    const long long recharge = R;
    long long work = 0;
    long long previous = 0;
    for (int i = 0; i < N; ++i) {
        const long long elapsed = A[i] - previous;
        const long long pending = ((elapsed <= work) ? (work - elapsed) : 0LL);
        if (!(pending <= recharge)) {
            return "NO";
        }
        work = pending + recharge;
        previous = A[i];
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
