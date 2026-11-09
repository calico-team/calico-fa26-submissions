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
void solve(int N, int R, vector<int>& A) {
	int chargenum = 2;
	int rechargetime = 0;
	int currenttime = 0;
	for(int i = 0; i < A.size(); i++){
        int cp = currenttime + rechargetime;
		switch(chargenum){
			case 2:
			//use the charge,
			chargenum--;
			rechargetime = R;
			break;
			case 1:
			//we have one charge, the other one is recharging
			
			//can the second one recharge before the required time?
			if(A[i] >= cp){
				chargenum = 1; // use the smoke
			}else{
				rechargetime -= A[i] - currenttime;// recharged a little
				chargenum = 0; // used the smoke
			}

			break;
			case 0:
			//we currently have no smokes

			//can we get a smoke before the required time?

			if(A[i] >= cp){
				//yes:
				currenttime += rechargetime;
				rechargetime = R;
				chargenum = 1;
				//can we get the second smoke before the required time?
				if(A[i] < cp + rechargetime){
					//no, second smoke recharges after the req
					//we wait until the ting
					rechargetime -= A[i] - currenttime;
					chargenum = 0;// we used the only smoke
				}
			}else{
				//we run out of smoke
				cout << "NO\n";
                return;
			}
			break;
		}

        currenttime = A[i];
	}

    cout << "YES\n";
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		solve(N, R, A);
	}
}
