#pragma GCC optimize("O3")


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
			chargenum--;
			rechargetime = R;
			currenttime = deadline;
		}
		else if(chargenum == 1){
			//we have one charge, the other one is recharging
			
			//can the second one recharge before the required time?
			if(deadline >= currenttime + rechargetime){
				//yes:
				chargenum = 1; // use the smoke
				rechargetime = R; //recharge setup
				currenttime = deadline; //update time
			}else{
				//no:
				rechargetime -= deadline - currenttime;// recharged a little
				chargenum = 0; // used the smoke
				currenttime = deadline;
			}
		}else{
			//we currently have no smokes

			if(deadline >= currenttime+ rechargetime + R){
				//we canfull charge
				chargenum = 1;
				rechargetime = R;
				currenttime = deadline;
			}else if(deadline >= currenttime + rechargetime){
				rechargetime = R - deadline + currenttime;
				currenttime = deadline;//we wait until the point
				chargenum = 0;// we used the only smoke
			}else{
				//we run out of smoke
				return "NO";
			}
		}
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
