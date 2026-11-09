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
	bool accepted = true;
    bool completed = false;
	int req = N;
	int seconds = R;
	vector<int> times = A;
	int time1 = times[0];
	int time2 = times[1];
	vector<int> charge1(N);
	vector<int> charge2(N);
	charge1[0] = time1;
	charge2[0] = time2;
	for (int i=0;i<N-1;i++){
            charge1[i+1] = charge1[i]+seconds;
    }
    for (int i=0;i<N-1;i++){
        charge2[i+1] = charge2[i]+seconds;
    }	
	bool recharge1 = false;
    bool recharge2 = false;

        for (int i=0;i<N;i++){
            completed = false;
            while (completed==false){
                if (times[i]<charge1[i]&&times[i]<charge2[i]){
                    recharge1 = true;
                    recharge2 = true;
                    accepted = false;
                    completed = true;
                }
                if (times[i]>=charge1[i]&&times[i]!=charge2[i]){
                    completed=true;
                    recharge1 = false;
                } else if (times[i]!=charge1[i]&&times[i]>=charge2[i]){
                    completed=true;
                    recharge2 = false;
                }
            }
        }
	if (accepted == true){
		return "YES";
	} else{
		return "NO";
	}
	
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
