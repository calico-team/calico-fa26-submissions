#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;

    vector<char> A(K);
    for (int i = 0; i < K; ++i) {
        cin >> A[i];
    }

    string hidden(N, '?');
    int known = 0;

    for (int i = 0; i < K; ++i) {
        if (known == N) break;

        char c = A[i];
        string guess(N, c);

        cout << guess << endl; // automatically flushes buffer

        string response;
        cin >> response;

        if (response == "CORRECT") {
            return;
        }

        for (int j = 0; j < N; ++j) {
            if (response[j] != '_') {
                hidden[j] = response[j];
                known++;
            }
        }
    }

    if (known == N) {
        cout << hidden << endl;
        string final_response;
        cin >> final_response;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
