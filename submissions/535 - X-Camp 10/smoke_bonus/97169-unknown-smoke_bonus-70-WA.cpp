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
	bool s1 = true, s2 = true;
	int cd1 = 0, cd2 = 0;
	int buffer = 0;
	for(int i = 0; i < A.size(); i++) {

		if(i != 0) {
			cd1 -= A[i] - A[i-1];
			if(cd1 <= 0) {
				buffer = abs(cd1);
				cd1 = 0;
				s1 = true;
			}
			cd2 -= buffer;
			buffer = 0;
			if(cd2 <= 0) {
				cd2 = 0;
				s2 = true;
			}
		}

		if(s1) {
			s1 = false;
			cd1 = R;
		}
		else if(s2) {
			s2 = false;
			cd2 = R;
		}
		else return "NO";
	}
	return "YES";
}
int main() {
	cin.tie(0); ios_base::sync_with_stdio(false);
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
