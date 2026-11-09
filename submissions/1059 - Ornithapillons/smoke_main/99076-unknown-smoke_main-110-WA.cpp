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
	int max;
	max = A.back();
	int recharger = 0;
	int recharger2 = 0;
	int charges = 0;
	string x = "YES";
	for (int i = 0; i <= max; i++){
		if (recharger == i) {
			recharger = 0;
			charges += 1;
		}
		if (recharger2 == i) {
			recharger2 = 0;
			charges += 1;
		}
		if (A[0] == i){
			if (charges == 1 or charges == 2){
				A.erase(A.begin());
				if (recharger == 0){
					recharger = R+i;
				} else {
					recharger2 = R+i;
				}
				charges --;
			} else {
				x = "NO";
			}
		} 
	}
	return x;
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
