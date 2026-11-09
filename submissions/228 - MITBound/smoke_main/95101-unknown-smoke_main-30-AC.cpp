#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int N, R;
		cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) cin >> A[i];
		int smoke1_status = 0;
		int smoke2_status = 0;
		int prev = 0;
		bool works = true;
		for (int i = 0; i < N; i++) {
			if (A[i] - prev >= smoke1_status) {
				if (A[i] - prev >= smoke2_status) {
					smoke2_status = 0;
				} else {
					smoke2_status -= A[i] - prev;
				}
				smoke1_status = 0;
			} else {
				smoke1_status -= prev;
			}
			if (!smoke2_status) {
				smoke2_status = R;
			} else if (!smoke1_status) {
				smoke1_status = smoke2_status;
				smoke2_status += R;
			} else {
				cout << "NO\n";
				works = false;
				break;
			}
			prev = A[i];
		}
		if (works) cout << "YES\n";
	}
}