#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<char> alpha(K);
        for (int i = 0; i < K; ++i) cin >> alpha[i];
        vector<char> fixedCh(N, 0);
        vector<int> idx(N, 0);
        string guess(N, alpha[0]);
        for (int round = 0; round < 100; ++round) {
            cout << guess << '\n' << flush;
            string resp;
            if (!(cin >> resp)) return 0;
            if (resp == "CORRECT") break;
            int m = (int)min<size_t>(N, resp.size());
            for (int i = 0; i < m; ++i) {
                if (resp[i] != '_') {
                    fixedCh[i] = 1;
                    guess[i] = resp[i];
                }
            }
            for (int i = 0; i < N; ++i) {
                if (!fixedCh[i]) {
                    idx[i] = (idx[i] + 1) % K;
                    guess[i] = alpha[idx[i]];
                }
            }
        }
    }
    return 0;
}
