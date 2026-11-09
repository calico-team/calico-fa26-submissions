#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long L_buf[200005];
long long R_buf[200005];
long long l_curr[200005];
long long r_curr[200005];
long long global_buf[300005];

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
            long long target = ans | (1LL << bit);
            int i_idx = 0;
            while (!(i_idx >= n)) {
                l_curr[i_idx] = L_buf[i_idx];
                r_curr[i_idx] = R_buf[i_idx];
                i_idx++;
            }

            long long min_xor = 0;
            long long max_xor = 0;

            i_idx = 0;
            while (!(i_idx >= n)) {
                long long l_val = l_curr[i_idx];
                long long r_val = r_curr[i_idx];

                long long cur_min = min(l_val, r_val);
                long long cur_max = max(l_val, r_val);

                min_xor ^= cur_min;
                max_xor ^= cur_max;
                i_idx++;
            }

            bit--;
        }

        t--;
    }
    return 0;
}
