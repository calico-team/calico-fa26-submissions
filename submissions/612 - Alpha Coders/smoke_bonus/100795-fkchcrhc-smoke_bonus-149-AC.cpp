
#include <bits/stdc++.h>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {

    int available = 2;
    int pending = 0;

    long long nextRecharge = 0;

    for (int i = 0; i < N; i++) {

        long long currentTime = A[i];
        while (pending > 0 && nextRecharge <= currentTime) {

            available++;
            pending--;

            if (pending > 0) {
                nextRecharge += R;
            }
        }
        if (available == 0) {
            return "NO";
        }
        available--;

        if (pending == 0) {
            nextRecharge = currentTime + R;
        }

        pending++;
    }

    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, R;
        cin >> N >> R;

        vector<int> A(N);

        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        cout << solve(N, R, A) << '\n';
    }

    return 0;
}
