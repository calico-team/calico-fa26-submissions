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
string solve(long long int N, long long int R, vector<long long int> A) {
	long long int ttlc=2, finish=-1;
	for(long long int i=0; i<N; i++) {
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
	long long int T;
	cin >> T;
	while (T--) {
		long long int N, R;
		cin >> N >> R;
		vector<long long int> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}