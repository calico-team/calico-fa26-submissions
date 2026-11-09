#include <iostream>
#include <vector>
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
	int chargito = 2;
	int cd = 99999999999;
    for (auto i : A) {
        for (chargito; chargito < 2 and cd <= i+1; chargito++) {
            cd += R;
        }
        if (chargito == 2) {
            cd = i+R;
            chargito -= 1;
        } else if (chargito == 0) {
            return "NO";
        } else {
            chargito -= 1;
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
