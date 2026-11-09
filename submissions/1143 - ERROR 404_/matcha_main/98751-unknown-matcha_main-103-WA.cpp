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

        // Process bits from high to low.
        // L[i], R[i] is the still-feasible interval for day i
        // given all higher bits of the xor already fixed.
        // Its interval is always inside one block of size 2^{b+1}.
        for (int b = 29; b >= 0; --b) {
            long long midBlock = 1LL << b;          // size of half block
            long long blockSize = 1LL << (b + 1);

            struct Both {
                int idx;
                long long len0, len1; // lengths of the two sub-intervals
                int best;             // bit giving larger sub-interval
            };
            vector<Both> both;
            both.reserve(N);

            int parity_fixed = 0;   // xor of bits forced to 0/1
            int parity_best = 0;    // xor if every flexible day takes its best bit

            vector<long long> len0_arr(N, -1), len1_arr(N, -1);
            vector<char> is_both(N, 0);
            vector<int> fixed_bit(N, 0);

            for (int i = 0; i < N; ++i) {
                long long l = L[i], r = R[i];
                long long block_start = (l / blockSize) * blockSize;
                long long mid = block_start + midBlock;
                if (r < mid) {
                    // only bit 0 possible
                    fixed_bit[i] = 0;
                    parity_fixed ^= 0;
                } else if (l >= mid) {
                    // only bit 1 possible
                    fixed_bit[i] = 1;
                    parity_fixed ^= 1;
                } else {
                    // both possible
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
            parity_best ^= parity_fixed; // parity_fixed is parity of fixed bits
            // parity_best now = xor of all bits if flexible days take best

            int chosen_bit; // xor bit we will achieve
            vector<char> flip(N, 0); // for flexible days, flip best -> alternative

            if (both.empty()) {
                chosen_bit = parity_fixed;
            } else if (parity_best == 1) {
                chosen_bit = 1;
                // keep best for everyone
            } else {
                // parity_best == 0, we need to flip one flexible day
                chosen_bit = 1;
                // 1) free flip: a tie (len0 == len1) loses nothing in length
                int tie_idx = -1;
                for (auto &bo : both) {
                    if (bo.len0 == bo.len1) { tie_idx = bo.idx; break; }
                }
                if (tie_idx != -1) {
                    flip[tie_idx] = 1;
                } else {
                    // 2) flip the day whose alternative interval is longest
                    //    (smallest loss of future freedom)
                    long long best_alt = -1;
                    int best_idx = -1;
                    for (auto &bo : both) {
                        long long alt = (bo.best == 0 ? bo.len1 : bo.len0);
                        if (alt > best_alt) {
                            best_alt = alt;
                            best_idx = bo.idx;
                        }
                    }
                    flip[best_idx] = 1;
                }
            }

            if (chosen_bit) answer |= (1LL << b);

            // Narrow every interval to the chosen sub-block.
            for (int i = 0; i < N; ++i) {
                if (!is_both[i]) continue;
                long long l = L[i], r = R[i];
                long long block_start = (l / blockSize) * blockSize;
                long long mid = block_start + midBlock;
                int best = (len0_arr[i] >= len1_arr[i] ? 0 : 1);
                int bit = flip[i] ? (best ^ 1) : best;
                if (bit == 0) {
                    R[i] = mid - 1;
                } else {
                    L[i] = mid;
                }
            }
        }

        cout << answer << '\n';
    }
    return 0;
}