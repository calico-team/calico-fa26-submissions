// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<char> chars(K);
        for (int i = 0; i < K; i++) {
            cin >> chars[i];
        }

        string answer(N, '?');
        bool solved = false;

        for (int j = 0; j < K - 1; j++) {
            string guess = answer;

            for (int i = 0; i < N; i++) {
                if (guess[i] == '?') {
                    guess[i] = chars[j];
                }
            }

            cout << guess << endl;
            string response;
            cin >> response;

            if (response == "CORRECT") {
                solved = true;
                break;
            }

            for (int i = 0; i < N; i++) {
                if (response[i] != '_') {
                    answer[i] = response[i];
                }
            }
        }

        if (!solved) {
            for (int i = 0; i < N; i++) {
                if (answer[i] == '?') {
                    answer[i] = chars[K - 1];
                }
            }

            cout << answer << endl;

            string response;
            cin >> response;
        }
    }
}