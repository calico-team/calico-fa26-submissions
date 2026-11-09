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
			//use the first charge on A[i], the second charge stays at 0, the first charge has a cooldown of R, and the time is now A[i]
			remaining_first = R;
			time = A[i];
		}else if(remaining_first != 0 && remaining_second == 0){
			//wait until the charge, in the meantime, decrease the cooldown of the first one by A[i] - time (the time we have until the next req)
			remaining_first -= A[i] - time;
			if(remaining_first <= 0){ // If it turns out that remaining_first had enough time to recharge during the waiting, then we use the first charge, and it has a cooldown of R.
				//remaining_first recharged, use first
				remaining_first = R;
				time = A[i];
			}else{
				//remaining_first did not recharge in time, continue using remaining_second
				remaining_second = R;
				time = A[i];
			}
		}else if(remaining_first == 0 && remaining_second != 0){
			//the first charge is ready, the second charge is recharging.
			remaining_second -= A[i] - time;// Wait until the req (in meantime: decrease the second charge's cooldown)
			if(remaining_second < 0){//if the second charge has finished cooling down, then save it for later
				remaining_second = 0;
			}
			//use first
			remaining_first = R;
			time = A[i];
		}else{
			//both smokes are unavailable, so we wait until the first charge happens
			if(A[i] < remaining_first + time){
				//If the first charge does not recharge in time for the req, then we cannot do it.
				return "NO";
			}
			//wait until first smoke recharges
			time += remaining_first;
			remaining_first = 0;
			//reconsider the situation
			remaining_second -= A[i] - time;
			if(remaining_second < 0) remaining_second = 0;
			remaining_first = R;
			time = A[i];
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
