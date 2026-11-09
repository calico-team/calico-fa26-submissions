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
	for (int i = 0; i > A.size(); i++){
		if (A[i] > max){
			max = A[i];
		}
	}
	int recharger = 0;
	int recharger2 = 0;
	int charges = 0;
	string x = "YES";
	for (int i = 0; i > max; i++){
		if (recharger - 1 >= 0){
			recharger --;
			if (recharger == 0){
				charges++;
			} 
		}
		if (recharger2 - 1 >= 0){
			recharger2 --;
			if (recharger2 == 0){
				charges++;
			} 
		}
		if (A[i] == i){
			if (charges >=1){
				A.erase(A.begin());
				if (recharger >0){
					recharger = R;
				} else {
					recharger2 = R;
				}
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
