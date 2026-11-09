#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int64> L(n), R(n);
        for (auto &x : L) cin >> x;
        for (auto &x : R) cin >> x;

        // Exact exhaustive search. This is a correctness-oriented reference
        // implementation, not suitable for the maximum constraints.
        int64 best = 0;

        function<void(int, int64)> dfs = [&](int i, int64 xr) {
            if (i == n) {
                best = max(best, xr);
                return;
            }

            for (int64 x = L[i]; x <= R[i]; ++x) {
                dfs(i + 1, xr ^ x);
                if (x == R[i]) break; // avoid overflow at the upper endpoint
            }
        };

        dfs(0, 0);
        cout << best << '\n';
    }

    return 0;
}
