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
	int chargeState1 = 1;
	int chargeState2 = 1;
	int c_time1 = 0;
	int c_time2 = 0;
	int prevTime = 0;
	
	for (int i = 0; i < N; i++) {
	    
	    if (chargeState1 == 0) {
	        if (A[i] - prevTime + c_time1 >= R) {
	            chargeState1 = 1;
	            c_time1 = A[i] - prevTime + c_time1 - R;
	        } else {
	            c_time1 += A[i] - prevTime;
	        }
	    } else if (chargeState2 == 0) {
	    	if (A[i] - prevTime + c_time2 >= R && chargeState1 == 1 && chargeState2 == 0) {
	            chargeState2 = 1;
	            c_time2 = A[i] - prevTime + c_time2 - R;
	        } else {
	            c_time2 += A[i] - prevTime;
	    }
	    }

	    

	    
	    
	    if (chargeState1 == 0 && chargeState2 == 0) {
	        return "NO";
	    }
	    
	    if (chargeState2 == 0) {
	        chargeState1 = 0;
	        c_time1 = 0;
	    } else {
	        chargeState2 = 0;
	        c_time2 = 0;
	    }
	    
	    prevTime = A[i];
	    
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
