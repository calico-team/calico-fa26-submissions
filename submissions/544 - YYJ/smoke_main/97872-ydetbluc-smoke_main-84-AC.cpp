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
	int chargenum = 2;
	int rechargetime = 0;
	int currenttime = 0;
	for(int i = 0; i < A.size(); i++){
		switch(chargenum){
			case 2:
			//use the charge,
			chargenum--;
			rechargetime = R;
			currenttime = A[i];
			break;
			case 1:
			//we have one charge, the other one is recharging
			
			//can the second one recharge before the required time?
			if(A[i] >= currenttime + rechargetime){
				//yes:
				rechargetime = 0; // finished recharging
				chargenum = 2; // we have 2 smokes now
				chargenum = 1; // use the smoke
				rechargetime = R; //recharge setup
				currenttime = A[i]; //update time
			}else{
				//no:
				rechargetime -= A[i] - currenttime;// recharged a little
				chargenum = 0; // used the smoke
				currenttime = A[i];
			}

			break;
			case 0:
			//we currently have no smokes

			//can we get a smoke before the required time?

			if(A[i] >= currenttime + rechargetime){
				//yes:
				currenttime += rechargetime;
				rechargetime = R;
				chargenum = 1;
				//can we get the second smoke before the required time?
				if(A[i] >= currenttime + rechargetime){
					//yes, the second smoke recharges before the req, we have 2 smokes
					chargenum = 2;
					rechargetime = 0;
					chargenum = 1; //we used a smoke
					rechargetime = R;
					currenttime = A[i];
				}else{
					//no, second smoke recharges after the req
					//we wait until the ting
					rechargetime -= A[i] - currenttime;
					currenttime = A[i];//we wait until the point
					chargenum = 0;// we used the only smoke
				}
			}else{
				//we run out of smoke
				return "NO";
			}
			break;
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
