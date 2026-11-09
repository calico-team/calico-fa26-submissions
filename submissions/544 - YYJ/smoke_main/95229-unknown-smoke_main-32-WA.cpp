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
	int remaining_first = 0;
	int remaining_second = 0;
	int time = 0;

	for(int i = 0; i < N; i++){
		if(remaining_first == 0 && remaining_second == 0){
			//use first
			remaining_first = R;
			time = A[i];
		}else if(remaining_first != 0 && remaining_second == 0){
			//use second
			remaining_second = R;
			//simulate passing time
			remaining_first -= A[i] - time;
			if(remaining_first < 0) remaining_first = 0;
			time = A[i];
		}else if(remaining_first == 0 && remaining_second != 0){
			remaining_second -= A[i] - time;
			//use first
			remaining_first = R;
			time = A[i];
		}else{
			//both smokes are unavailable
			if(A[i] < remaining_first + time && A[i] < remaining_second + time) return "NO";
			
			if(A[i] >= remaining_first + time && A[i] < remaining_second + time){
				//first smoke recharges within the time
				time += remaining_first;
				remaining_first = 0;
				i--;
			}else if(A[i] < remaining_first + time && A[i] >= remaining_second + time){
				//second smoke recharges within the time
				time += remaining_second;
				remaining_second = 0;
				i--;
			}else{
				//Both smokes recharge within the time
				if(remaining_first < remaining_second){
					//remaining_first charges first
					time += remaining_first;
					remaining_first = 0;
					i--;
				}else{
					//second charges first
					time += remaining_second;
					remaining_second = 0;
					i--;
				}
			}
		}
		;
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
