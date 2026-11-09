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
	int recharger = 0;
	int queue = 0;
	int charges = 2;
	string x = "YES";
	for (int i = 0; i < A.size(); i ++) {
		if (recharger <= A[i] && recharger != 0){
			recharger = 0;
			if (charges < 2){
						charges = charges + 1;
					}
			if (queue > 0){
				queue --;
				recharger = recharger + R;
				if (recharger <= A[i] && recharger != 0){
					recharger = 0;
					if (charges < 2){
						charges = charges + 1;
					}
				}
			}
		}
		if (charges > 0){
			charges --;
			if (recharger > 0){
				queue += 1;
			} else{
				recharger = A[i] + R;
			}
		} else {
			x = "NO";
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
