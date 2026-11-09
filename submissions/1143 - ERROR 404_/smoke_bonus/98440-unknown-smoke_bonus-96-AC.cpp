#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        long long R;
        cin >> N >> R;
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) cin >> A[i];

        // completion times of charges currently recharging, in order.
        // At most 2, because we have at most 2 charges.
        deque<long long> q;
        bool ok = true;

        for (int i = 0; i < N; ++i) {
            long long t = A[i];

            // Recharges are processed before requests at the same time.
            while (!q.empty() && q.front() <= t) q.pop_front();

            // Available charges = 2 - recharging
            if ((int)q.size() >= 2) {
                ok = false;
                break;
            }

            // Use one charge.
            // If none recharging: it starts recharging now.
            // If one recharging: this one starts only after that one
            // finishes, i.e. at q.front().
            long long completion;
            if (q.empty()) {
                completion = t + R;
            } else {
                completion = q.front() + R;
            }
            q.push_back(completion);
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}