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
	int ttlc=2, finish=-1;
	for(int i=0; i<N; i++) {
		while(finish!=-1 && finish <=A[i]) {
			ttlc+=1;
			if(ttlc==1) {
				finish+=R;
			}
			else finish=-1;
		}

		if(ttlc>0) {
			if(ttlc==2 && finish==-1) {
				finish=A[i]+R;
			}
			ttlc--;
		}
		else return "NO";
	}
	return "YES";
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