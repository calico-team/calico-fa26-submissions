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
	string ans;
	int smokes = 2, marker = 0;
	for(int i = 0; i<A.size(); i++){
	    if(A[i] >= marker + R){
	        smokes++;
	        if(smokes>2) smokes--;
	        if(smokes == 1 && A[i]>=marker + (2 * R)){
	            smokes++;
	            if(smokes>2) smokes--;
	        }
	    }
	    smokes--;
	    marker = A[i];
	    if(smokes == -1) return "NO";
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
