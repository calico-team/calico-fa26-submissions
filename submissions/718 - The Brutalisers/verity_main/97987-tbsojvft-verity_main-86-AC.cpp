#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        vector<char> A(K);
        for (char &c : A) cin >> c;
        string G(N, '_');
        for (int t = 0;; t++) {
            string S = G;
            for (char &c : S) if (c == '_') c = A[min(t, K - 1)];
            cout << S << endl;
            string R; cin >> R;
            if (R == "CORRECT" || R.size() != N) break;
            for (int j = 0; j < N; j++) if (R[j] != '_') G[j] = R[j];
        }
    }
}