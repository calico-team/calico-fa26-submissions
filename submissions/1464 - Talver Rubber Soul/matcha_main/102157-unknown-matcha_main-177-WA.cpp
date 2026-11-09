#include <bits/stdc++.h> 
using namespace std;

/**
 * Return the maximum possible value of X, Big Ben's matcha enjoyment.
 * N: the days in Big Ben's life
 * L: the lower bound of enjoyment from each store
 * R: the upper bound of enjoyment from each store
 */
long long solve(int N, vector<int> L, vector<int> R) {
long long max_enjoyment = 0;

    for (int b = 29; b >= 0; b--) {
        long long must_one = 0;
        long long flexible = 0;

        for (int i = 0; i < N; i++) {
            long long l_prefix = L[i] >> (b + 1);
            long long r_prefix = R[i] >> (b + 1);

            if (l_prefix < r_prefix) {
                flexible++;
            } else {
                long long lb = (L[i] >> b) & 1;
                long long rb = (R[i] >> b) & 1;
                if (lb == 1 && rb == 1) {
                    must_one++;
                } else if (lb == 0 && rb == 1) {
                    flexible++;
}
}
}

        bool can_make_one = (flexible > 0) || (must_one % 2 == 1);

        if (can_make_one) {
            max_enjoyment |= (1LL << b);
            bool need_one = (must_one % 2 == 0);

            for (int i = 0; i < N; i++) {
                long long l_prefix = L[i] >> (b + 1);
                long long r_prefix = R[i] >> (b + 1);
                long long lb = (L[i] >> b) & 1;
                long long rb = (R[i] >> b) & 1;
                bool is_flex = (l_prefix < r_prefix) || (lb == 0 && rb == 1);

                if (is_flex) {
                    long long prefix_mask = ~((1LL << (b + 1)) - 1);
                    if (need_one) {
                        // Force bit b to 1 and cap R[i] to this prefix
                        L[i] = max((long long)L[i], (L[i] & prefix_mask) | (1LL << b));
                        R[i] = min((long long)R[i], (L[i] & prefix_mask) | ((1LL << (b + 1)) - 1));
                        need_one = false;
                    } else {
                        // Force bit b to 0
                        if (lb == 0) {
                            R[i] = min((long long)R[i], (L[i] & prefix_mask) | ((1LL << b) - 1));
                        } else {
                            L[i] = (l_prefix + 1) << (b + 1);
                            R[i] = min((long long)R[i], L[i] | ((1LL << b) - 1));
                        }
}
}
}
        } else {
            for (int i = 0; i < N; i++) {
                long long l_prefix = L[i] >> (b + 1);
                long long r_prefix = R[i] >> (b + 1);
                long long lb = (L[i] >> b) & 1;
                long long rb = (R[i] >> b) & 1;
                bool is_flex = (l_prefix < r_prefix) || (lb == 0 && rb == 1);

                if (is_flex) {
                    long long prefix_mask = ~((1LL << (b + 1)) - 1);
                    if (lb == 0) {
                        R[i] = min((long long)R[i], (L[i] & prefix_mask) | ((1LL << b) - 1));
                    } else {
                        L[i] = (l_prefix + 1) << (b + 1);
                        R[i] = min((long long)R[i], L[i] | ((1LL << b) - 1));
                    }
}
}
}
}
    return max_enjoyment;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<int> L(N), R(N);
            for (int i = 0; i < N; i++) cin >> L[i];
            for (int i = 0; i < N; i++) cin >> R[i];
            cout << solve(N, L, R) << "\n";
        }
    }
    return 0;
}