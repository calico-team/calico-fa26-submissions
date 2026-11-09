#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int i = 0; i < K; i++)
            cin >> A[i];

        string answer(N, '?');

        for (int i = 0; i < K; i++) {
            string guess = answer;

            for (int j = 0; j < N; j++) {
                if (guess[j] == '?')
                    guess[j] = A[i];
            }

            cout << guess << endl;

            string response;
            cin >> response;

            if (response == "CORRECT")
                break;

            for (int j = 0; j < N; j++) {
                if (response[j] != '_')
                    answer[j] = response[j];
            }
        }
    }

    return 0;
}
