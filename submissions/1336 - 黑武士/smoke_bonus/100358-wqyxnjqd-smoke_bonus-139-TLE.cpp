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
string solve(int N, int R, vector<long long> A) {
	// YOUR CODE HERE
	int charges = 2;
	int timer = 0;
	for(int i=0;i<N;i++){
		bool flag = false; //recharged one
		//calculate replenished charges
		if((A[i]-timer)/R>=2 || i==0){ //2 recharged
			charges = 2;
		}else if((A[i]-timer)/R==1){ //1 recharged
			flag = true;
			charges++;
			if(charges>=2)
				charges=2;
		}
		
		//update timer
		if(charges == 2){
			timer = A[i];
		}else if(flag){
			timer += R;
		}

		if(charges==0){
			return "NO";
		}
		charges--;
//		cout<<"charges after A["<<i<<"]: "<<charges<<", charge countdown started at: "<<timer<<endl;
	}
	return "YES";
}

int main() {
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<long long> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}

