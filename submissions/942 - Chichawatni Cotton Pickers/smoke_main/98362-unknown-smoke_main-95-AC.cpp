#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string solve(int N, int R, vector<int> A) {
    vector<long long> ready = {0, 0};

    for (int i = 0; i < N; i++) {
        long long t = A[i];

        int chosen = -1;
        for (int j = 0; j < 2; j++) {
            if (ready[j] <= t) {
                if (chosen == -1 || ready[j] < ready[chosen]) {
                    chosen = j;
                }
            }
        }

        if (chosen == -1) {
            return "NO";
        }

        int other = 1 - chosen;
        ready[chosen] = max(t, ready[other]) + R;
    }

    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N, R;
        cin >> N >> R;
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        cout << solve(N, R, A) << "\n";
    }

    return 0;
}