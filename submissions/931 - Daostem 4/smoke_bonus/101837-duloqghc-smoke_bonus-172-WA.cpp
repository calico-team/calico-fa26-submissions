#include <bits/stdc++.h>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
	int smokes = 2;
	int marker1, marker2;
	vector<long long> v{LLONG_MAX,LLONG_MAX};

	for(size_t i = 0; i<A.size(); i++){
		//sort so that the recharge times are in order
		sort(v.begin(),v.end());
		//recharge
		if(A[i]>=v[0]){
			smokes++;
			v[0] = INT_MAX;
		}
		if(A[i]>=v[1]){
			smokes++;
			v[1] = INT_MAX;
		}
		//firing
		smokes--;
		//check
		if(smokes<0) return "NO";

		if(v[0] == INT_MAX){
			v[0] = A[i]+R;
		}
		else{
			v[1] = v[0]+ R;
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
