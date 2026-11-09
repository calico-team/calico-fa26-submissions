// Source: https://usaco.guide/general/io

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
    int c = 2;
    int r = -1;
    int w = 0;
    for (int i = 0; i < N; i++) {
        while (r != -1 && r <= A[i]) {
            c++;
            if (w > 0) {
                w--;
                r += R;
            }
            else {
                r = -1;
            }
        }
        if (c == 0) return "NO";
        c--;
        if (r == -1) {
            r = A[i] + R;
        }
        else {
            w++;
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