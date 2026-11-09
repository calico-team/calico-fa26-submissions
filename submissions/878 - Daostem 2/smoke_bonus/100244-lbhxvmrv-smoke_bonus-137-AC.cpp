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
string solve(ll N, ll R, vector<ll>& A) {
	ll c1=0, c2=0;
	for(ll i=0; i<N; i++){
	    if(c1>A[i] && c2>A[i]){
	        return "NO"; 
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
			
}

int main() {
    //from the schedule problem...
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	ll T;
	cin >> T;
	while (T--) {
		ll N, R;
		cin >> N >> R;
		vector<ll> A(N);
		for (ll i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}