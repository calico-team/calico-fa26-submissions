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
 
using ll=long long;
string solve(long long int N, long long int R, vector<long long int> A) {
	ll c1=0, c2=0;
	for(ll i=0; i<N; i++){
	    if(c1>A[i] && c2>A[i]){
	        return "NO"; //pls work
	    }
	    if(c1<=A[i]){
	        if(c2>A[i]) c1=c2+R;
	        else c1=A[i]+R;
	    }
	    else{
	        if(c1>A[i]) c2=c1+R;
	        else c2=A[i]+R;
	    }
	}

	return "YES";
	//r u gonna work pls work bro
			
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