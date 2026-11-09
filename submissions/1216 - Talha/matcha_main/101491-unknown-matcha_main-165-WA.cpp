#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int L, R;
    int type; // 0: Free, 1: Lower-bounded, 2: Upper-bounded, 3: Both-bounded
};

int solve(int N, vector<int> L, vector<int> R) {
    if (N == 1) return R[0];

    vector<Interval> intervals(N);
    for (int i = 0; i < N; i++) {
        intervals[i] = {L[i], R[i], 3};
    }

    int ans = 0;
    int num_free = 0;

    for (int k = 29; k >= 0; k--) {
        if (num_free > 0) {
            ans |= ((1 << (k + 1)) - 1);
            break;
        }

        int fixed_parity = 0;
        int flexible_cnt = 0;
        int liberator_cnt = 0;

        for (int i = 0; i < N; i++) {
            if (intervals[i].type == 0) continue;
            int bit_l = (intervals[i].L >> k) & 1;
            int bit_r = (intervals[i].R >> k) & 1;

            if (intervals[i].type == 3) {
                if (bit_l == bit_r) {
                    fixed_parity ^= bit_l;
                } else {
                    flexible_cnt++;
                }
            } else if (intervals[i].type == 1) {
                if (bit_l == 1) {
                    fixed_parity ^= 1;
                } else {
                    flexible_cnt++;
                    liberator_cnt++;
                }
            } else if (intervals[i].type == 2) {
                if (bit_r == 0) {
                    fixed_parity ^= 0;
                } else {
                    flexible_cnt++;
                    liberator_cnt++;
                }
            }
        }

        if (liberator_cnt > 0) {
            if (flexible_cnt >= 2) {
                ans |= ((1 << (k + 1)) - 1);
                break;
            } else {
                // flexible_cnt == 1, exactly one liberator
                int lib_idx = -1;
                for (int i = 0; i < N; i++) {
                    if (intervals[i].type == 1 && ((intervals[i].L >> k) & 1) == 0) lib_idx = i;
                    if (intervals[i].type == 2 && ((intervals[i].R >> k) & 1) == 1) lib_idx = i;
                }
                int bit_to_free = (intervals[lib_idx].type == 1) ? 1 : 0;
                if ((fixed_parity ^ bit_to_free) == 1) {
                    ans |= ((1 << (k + 1)) - 1);
                    break;
                } else {
                    ans |= (1 << k);
                    // Stay bounded
                    continue;
                }
            }
        }

        // liberator_cnt == 0
        if (flexible_cnt == 0) {
            ans |= (fixed_parity << k);
        } else {
            ans |= (1 << k);
            int needed_flexible_parity = 1 ^ fixed_parity;
            int ones_needed = (needed_flexible_parity == 1) ? 1 : (flexible_cnt >= 2 ? 2 : 0);

            for (int i = 0; i < N; i++) {
                if (intervals[i].type == 3 && (((intervals[i].L >> k) & 1) != ((intervals[i].R >> k) & 1))) {
                    if (ones_needed > 0) {
                        intervals[i].type = 2; // chose 1
                        ones_needed--;
                    } else {
                        intervals[i].type = 1; // chose 0
                    }
                }
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> L(N), R(N);
        for (int& i : L) cin >> i;
        for (int& i : R) cin >> i;
        cout << solve(N, L, R) << '\n';
    }
    return 0;
}