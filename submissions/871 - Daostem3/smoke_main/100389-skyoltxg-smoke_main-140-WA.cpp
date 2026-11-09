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
	int smokecharge=2;
	int timecounter=0;
	int t; //basically i just need to figure out the amount of times i need to run it

	for(int i=0; i<A.size(); i++) {
		if(A[i]<R) {
			smokecharge--;
		}
		else {
			cout<<"YES";
			break;
		}
		while(smokecharge<2) {
			timecounter+=R;
			if(timecounter>A[i]) {
				return "NO";
				i++;

			}

			else if(timecounter<A[i]) {
				if(i<N) {
					i++;
					continue;
				}
				else if(i==N) {
					return "YES";

				}
			}
		}
	}

	return "";
}



int main() {
	int T;
	cin >> T;
	while (T--) {
		int N, R;
		cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
