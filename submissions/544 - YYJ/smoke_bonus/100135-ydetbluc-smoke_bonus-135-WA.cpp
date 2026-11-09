
#include <iostream>
#include <vector>
using namespace std;

int nums[100001];

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R) {
	int chargenum = 2;
	int rechargetime = 0;
	int currenttime = 0;
	for(int i = 0; i < N; i++){
		int deadline = nums[i];
		if(chargenum == 2){
			chargenum = 1;
			rechargetime = R;
		}
		else if(chargenum == 1){
			//we have one charge, the other one is recharging
			
			//can the second one recharge before the required time?
			if(deadline >= currenttime + rechargetime){
				//yes:
				chargenum = 1; // use the smoke
				rechargetime = R; //recharge setup
			}else{
				//no:
				rechargetime -= deadline - currenttime;// recharged a little
				chargenum = 0; // used the smoke
			}
		}else{
			// if(deadline < currenttime + rechargetime) return "NO";

			// currenttime += rechargetime;
			// rechargetime = R;
			// chargenum = 1;
			// if(deadline >= currenttime + R){
			// 	//we canfull charge
			// 	chargenum = 1;
			// 	rechargetime = R;
			// 	currenttime = deadline;
			// }else{
			// 	rechargetime -= R - deadline + currenttime;
			// 	currenttime = deadline;//we wait until the point
			// 	chargenum = 0;// we used the only smoke
			// }
			


			//we currently have no smokes
			
			//can we get a smoke before the required time?
			
			if(deadline < currenttime + rechargetime) return "NO";

			if(deadline >= currenttime + rechargetime + R){
				chargenum = 1; //we used a smoke
				rechargetime = R;
			}else{
				rechargetime = R - deadline + currenttime + R;
				chargenum = 0;// we used the only smoke
			}
		}
		currenttime = deadline;
	}

	return "YES";
}

int main() {
	//freopen("fout.in","r",stdin);
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		cout << solve(N, R) << "\n";
	}
}
