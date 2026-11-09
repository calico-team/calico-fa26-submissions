#include <iostream>
using namespace std;

string solve(int N, int R, int A[]) {
	int cnt=0, smoke=1;
	for(int i=1; i< N; i++){
		smoke--;
		if(A[i]-A[i-1] >= R && smoke < 2){
			smoke ++;
		}
	}
	if (smoke>0 || smoke ==0) return "YES";
	else return "NO";
}

int main() {
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		int A[100005];
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
