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
	int smokes = 2;
	int time = 0;
	int recharge = R;
	for(int i = 0; i < N; i++){
		if(smokes == 2){
			time = A[i];
			recharge = R;
			smokes--;
		} else if(smokes == 1){
			recharge -= A[i] - time;
			time = A[i];
			smokes--;
			if(recharge <= 0){
				recharge = R;
				smokes++;
			}
		} else {
			recharge -= A[i] - time;
			if(recharge <= -1 * R){
				smokes += 1;
			}
			else if(recharge <= 0){

			} else return "NO";
			recharge = R;
			time = A[i];
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
