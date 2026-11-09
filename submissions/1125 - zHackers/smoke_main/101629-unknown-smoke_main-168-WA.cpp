#include <iostream>
#include <vector>
using namespace std;

string solve(int N, int R, vector<int> A) {
	int sec1 = 0;
	int sec2 = 0;
	
	for (int i=0; i<N; i++){
		int a = A[i];
		if (a < sec1){
			return "NO";
		}
		
		sec1 = max(a , sec2) + R;
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
