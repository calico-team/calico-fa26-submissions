#include<bits/stdc++.h>
using namespace std;


int mergeRange(int a, int b) {
    int mask = a & b;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;
    return a | b | mask;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<int> l(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &l[i]);
        }

        vector<pair<int, int>> ranges;
        int fixed = 0;

        for (int i = 0; i < n; i++) {
            int r;
            scanf("%d", &r);
            if (l[i] == r) {
                fixed ^= r;
            } else {
                ranges.push_back({l[i], r});
            }
        }

        int ans = 0;

        for (int bit = 29; bit >= 0; bit--) {
            int mask = (1 << bit) - 1;
            int parity = (fixed >> bit) & 1;
            int cnt = 0;
            int dp[2] = {0, -1};
            vector<pair<int, int>> next;
            next.reserve(ranges.size());

            for (auto range : ranges) {
                int low = range.first;
                int high = range.second;

                if ((low >> bit) == (high >> bit)) {
                    parity ^= (low >> bit) & 1;
                    next.push_back({low & mask, high & mask});
                    continue;
                }

                cnt++;
                int bound0 = mask - low;
                int bound1 = high & mask;
                int ndp[2] = {-1, -1};

                // Track the parity of how many upper halves we choose.
                for (int p = 0; p < 2; p++) {
                    if (dp[p] == -1) continue;

                    ndp[p] = max(ndp[p], mergeRange(dp[p], bound0));
                    ndp[p ^ 1] = max(ndp[p ^ 1], mergeRange(dp[p], bound1));
                }

                dp[0] = ndp[0];
                dp[1] = ndp[1];
            }

            fixed &= mask;

            if (cnt == 0) {
                if (parity == 1) ans |= (1 << bit);
            } else {
                ans |= (1 << bit);
                int need = parity ^ 1;

                
                if (((cnt & 1) ^ need) != 0) {
                    fixed ^= mask;
                }

                next.push_back({0, dp[need]});
            }

            ranges.swap(next);
        }

        printf("%d\n", ans);
    }

    return 0;
}
