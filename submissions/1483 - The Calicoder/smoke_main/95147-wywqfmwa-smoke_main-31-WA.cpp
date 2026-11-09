// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, R;
        cin >> N >> R;
        vector<int> A(N);
        int count = 0;
        for (int n = 0; n < N; n++) {
            cin >> A[n];
            if (n > 0 && A[n] - A[n - 1] >= R) {
                count++;
            }
        }
        if (count == N - 1) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
