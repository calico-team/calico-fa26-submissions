#include <iostream>
using namespace std;

string solve(int N, int R, int A[]) {
	int cnt=0;
	int smoke=1;
	int next = A[0] + R;
	for(int i=1; i< N; i++){
		smoke--;
		if((A[i] > next ||A[i] == next) && smoke < 2){
            int num = A[i]-A[i-1];
			smoke += num/R;
			next = A[i] + R;
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