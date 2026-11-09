#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string solve(int N, int R, vector<int>& A) {
    long long c1 = 0, c2 = 0;       // Timestamps when charge 1 and charge 2 become available
    long long busy_until = 0;     // Timestamp when the sequential recharge station finishes

    for (int i = 0; i < N; i++) {
        long long t = A[i];
        // If the earliest ready charge is not available by timestamp t, request fails
        if (t < c1) {
            return "NO";
        }
        // Use charge c1. The recharge starts after max(t, busy_until)
        long long new_ready = max(t, busy_until) + R;
        busy_until = new_ready;
        c1 = new_ready;

        // Keep c1 <= c2 so c1 is always the earlier available charge
        if (c1 > c2) swap(c1, c2);
    }
    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, R;
        cin >> N >> R;
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        cout << solve(N, R, A) << "\n";
    }
    return 0;
}