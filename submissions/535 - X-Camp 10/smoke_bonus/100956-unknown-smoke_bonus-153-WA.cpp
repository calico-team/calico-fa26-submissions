#include <bits/stdc++.h>
using namespace std;

string solve(int N, int R, vector<int> A) {
	int next1 = 0, next2 = 0;
	for(int i = 0; i < A.size(); i++) {
        if(A[i] < next1 && A[i] < next2) return "NO";
        if(A[i] >= next1) {
            next1 = A[i] + R;
            next2 = max(next2, next1) + R;
        }
        else {
            next2 = next1 + R;
        }
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
