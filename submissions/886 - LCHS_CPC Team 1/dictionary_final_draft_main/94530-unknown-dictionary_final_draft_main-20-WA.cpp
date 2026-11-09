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
	int charges = 2;
	int c_time = 0;
	int s_time = 0;
	for (int i = 0; i < N; i++) {
	    
	    if (A[i] - c_time + s_time >= R) {
	        if (charges < 2) {
	            charges++;
	            s_time = 0;
	        }
	    } else {
	        s_time = s_time + A[i] - c_time;
	    }
	    
	    if (charges == 0) {
	        return "NO";
	    }
	    
	    charges--;
	    c_time = A[i];
	    
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
