#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long L_buf[200005];
long long R_buf[200005];

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        int n;
        cin >> n;

        int i = 0;
        while (!(i >= n)) {
            cin >> L_buf[i];
            i++;
        }

        i = 0;
        while (!(i >= n)) {
            cin >> R_buf[i];
            i++;
        }

        long long ans = 0;
        int bit = 29;

        while (!(bit < 0)) {
            long long target_bit = 1LL << bit;
            long long min_xor = 0;
            long long max_xor = 0;
            int can_force_parity = 0;
            int total_parity_min = 0;

            int i_idx = 0;
            while (!(i_idx >= n)) {
                long long l_val = L_buf[i_idx];
                long long r_val = R_buf[i_idx];

                // Check if we can choose between having bit set or not within [l_val, r_val]
                // Specifically, does the range cross a multiple of 2^(bit+1) or contain both bit=0 and bit=1 options?
                long long mask = (1LL << (bit + 1)) - 1;
                long long low_rem = l_val & mask;
                long long high_rem = r_val & mask;

                long long base_val = l_val & ~mask;
                
                // If r_val - l_val >= target_bit, we can definitely choose either 0 or 1 for this bit
                if (!(r_val - l_val < target_bit)) {
                    can_force_parity = 1;
                } else {
                    // Check if low_rem and high_rem span across target_bit
                    if (!((low_rem < target_bit && high_rem < target_bit) || (low_rem >= target_bit && high_rem >= target_bit))) {
                        can_force_parity = 1;
                    }
                }

                long long chosen_min = l_val;
                if (!((l_val & target_bit) == 0)) {
                    min_xor ^= target_bit;
                    total_parity_min ^= 1;
                }
                i_idx++;
            }

            // Let's implement the standard greedy bit check:
            // We want to see if we can get a 1 at the current bit in the total XOR sum.
            long long cur_ans = ans | target_bit;
            
            // To test if cur_ans is achievable with a prefix matching ans on higher bits:
            // For each interval, we can choose a value that matches the preferred bit if possible.
            long long test_xor = 0;
            int forced_count = 0;
            int flexible_count = 0;

            i_idx = 0;
            while (!(i_idx >= n)) {
                long long l_val = L_buf[i_idx];
                long long r_val = R_buf[i_idx];
                
                // Try to choose value such that its bit matches the target bit of cur_ans
                // If the interval allows choosing either 0 or 1 for this bit:
                long long mask = (1LL << (bit + 1)) - 1;
                long long low_rem = l_val & mask;
                long long high_rem = r_val & mask;

                bool flexible = false;
                if (!(r_val - l_val < target_bit)) {
                    flexible = true;
                } else {
                    if (!((low_rem < target_bit && high_rem < target_bit) || (low_rem >= target_bit && high_rem >= target_bit))) {
                        flexible = true;
                    }
                }

                if (flexible) {
                    flexible_count++;
                    // We can choose the endpoint that gives bit = 1 (if we want 1) or bit = 0 (if we want 0)
                    // Greedily pick the one that matches our desired bit for this position
                } else {
                    if (!((l_val & target_bit) == 0)) {
                        test_xor ^= target_bit;
                        forced_count ^= 1;
                    }
                }
                i_idx++;
            }

            // If flexible_count > 0, we can adjust parity freely, so we can always achieve the 1 bit.
            // If flexible_count == 0, we must check if forced_count has the correct parity.
            bool achievable = false;
            if (!(flexible_count == 0)) {
                achievable = true;
            } else {
                if (!(forced_count == 1)) {
                    achievable = true;
                }
            }

            if (achievable) {
                ans = cur_ans;
            }

            bit--;
        }

        cout << ans << "\n";
        t--;
    }
    return 0;
}
