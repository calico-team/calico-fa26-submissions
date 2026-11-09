#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        char A[30];
        for (int i = 0; i < K; i++) {
            cin >> A[i];
        }

        string ans = "";
        for (int i = 0; i < N; i++) {
            ans = ans + A[0];
        }

        bool done = false;
        for (int j = 0; j < K; j++) {
            string guess = "";
            for (int i = 0; i < N; i++) {
                guess = guess + A[j];
            }

            cout << guess << endl;
            cout.flush();

            string res;
            cin >> res;
            if (res == "CORRECT") {
                done = true;
                break;
            }

            for (int i = 0; i < N; i++) {
                if (res[i] != '_') {
                    ans[i] = A[j];
                }
            }
        }

        if (done == false) {
            cout << ans << endl;
            cout.flush();
            string res;
            cin >> res;
        }
    }
    return 0;
}
