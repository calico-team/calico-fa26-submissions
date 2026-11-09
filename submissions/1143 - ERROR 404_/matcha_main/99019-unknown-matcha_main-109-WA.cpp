#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> L(N), R(N);
        for (int i = 0; i < N; ++i) cin >> L[i];
        for (int i = 0; i < N; ++i) cin >> R[i];

        long long answer = 0;

        // Bits high -> low. L[i],R[i] is the still-feasible interval
        // for day i given the higher xor bits already fixed.
        for (int b = 29; b >= 0; --b) {
            long long blockSize = 1LL << (b + 1);
            long long midBlock = 1LL << b;

            struct Both { int idx; long long len0, len1; int best; };
            vector<Both> both;
            both.reserve(N);

            vector<long long> len0_arr(N, -1), len1_arr(N, -1);
            vector<char> is_both(N, 0);
            int parity_fixed = 0;
            int parity_best = 0;

            for (int i = 0; i < N; ++i) {
                long long l = L[i], r = R[i];
                long long block_start = (l / blockSize) * blockSize;
                long long mid = block_start + midBlock;
                if (r < mid) {
                    // only bit 0
                } else if (l >= mid) {
                    // only bit 1
                    parity_fixed ^= 1;
                } else {
                    is_both[i] = 1;
                    long long len0 = mid - l;
                    long long len1 = r - mid + 1;
                    len0_arr[i] = len0;
                    len1_arr[i] = len1;
                    int best = (len0 >= len1 ? 0 : 1);
                    both.push_back({i, len0, len1, best});
                    parity_best ^= best;
                }
            }
            parity_best ^= parity_fixed;

            vector<char> flip(N, 0);
            int chosen_bit;
            if (both.empty()) {
                chosen_bit = parity_fixed;
            } else if (parity_best == 1) {
                chosen_bit = 1; // keep everyone's best bit
            } else {
                chosen_bit = 1; // must flip exactly one flexible day
                // Flip the day with smallest loss (best-alt),
                // tie-break by smallest best length.
                // A tie len0==len1 has loss 0, so it is chosen first.
                long long best_loss = LLONG_MAX;
                long long best_len = LLONG_MAX;
                int best_idx = -1;
                for (auto &bo : both) {
                    long long bl = (bo.best == 0 ? bo.len0 : bo.len1);
                    long long al = (bo.best == 0 ? bo.len1 : bo.len0);
                    long long loss = bl - al;
                    if (loss < best_loss ||
                        (loss == best_loss && bl < best_len)) {
                        best_loss = loss;
                        best_len = bl;
                        best_idx = bo.idx;
                    }
                }
                flip[best_idx] = 1;
            }

            if (chosen_bit) answer |= (1LL << b);

            // Narrow to the chosen sub-block.
            for (int i = 0; i < N; ++i) {
                if (!is_both[i]) continue;
                long long l = L[i], r = R[i];
                long long block_start = (l / blockSize) * blockSize;
                long long mid = block_start + midBlock;
                int best = (len0_arr[i] >= len1_arr[i] ? 0 : 1);
                int bit = flip[i] ? (best ^ 1) : best;
                if (bit == 0) R[i] = mid - 1;
                else          L[i] = mid;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}