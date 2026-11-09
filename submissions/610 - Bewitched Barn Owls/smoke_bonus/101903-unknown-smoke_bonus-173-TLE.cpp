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
	int x[2] = {0,0};
	for(int i = 0; i <N;i++){
		if ((i%2) == 0){
			if(x[0]> A[i]){
				return "No";
			}
			x[0] = (A[i]>=x[1])? (A[i]+R): (x[1]+R);
		}
		else
		{
			if(x[1]>A[i]){
				return "No";
			}
			x[1] = (A[i]>=x[0])? (A[i]+R): (x[0]+R);
		}
	}
	return "Yes";
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
