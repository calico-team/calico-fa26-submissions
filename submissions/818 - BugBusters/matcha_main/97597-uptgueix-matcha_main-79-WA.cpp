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

        vector<int> L(N), R(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        for (int i = 0; i < N; i++) cin >> R[i];

        // nextLow[i][b] = greatest bit below b where L[i] has bit 0.
        // nextHigh[i][b] = greatest bit below b where R[i] has bit 1.
        vector<array<int, 31>> nextLow(N), nextHigh(N);

        for (int i = 0; i < N; i++) {
            int bestL = -1, bestH = -1;
            nextLow[i][0] = -1;
            nextHigh[i][0] = -1;

            for (int b = 0; b < 30; b++) {
                if (((L[i] >> b) & 1) == 0) bestL = b;
                if (((R[i] >> b) & 1) == 1) bestH = b;

                nextLow[i][b + 1] = bestL;
                nextHigh[i][b + 1] = bestH;
            }

            nextLow[i][0] = -1;
            nextHigh[i][0] = -1;
        }

        // State: 0 = free, 1 = tight-low, 2 = tight-high, 3 = both.
        vector<int> state(N, 3);
        long long ans = 0;

        for (int b = 29; b >= 0; --b) {
            struct Opt {
                int bit;
                int ns;
                int score;
            };

            vector<array<Opt, 2>> opts(N);
            vector<int> cnt(N, 0);
            vector<int> choice(N, 0);
            int parity = 0;

            auto scoreLow = [&](int i) { return nextLow[i][b]; };
            auto scoreHigh = [&](int i) { return nextHigh[i][b]; };

            for (int i = 0; i < N; i++) {
                int st = state[i];
                int lb = (L[i] >> b) & 1;
                int rb = (R[i] >> b) & 1;

                if (st == 0) {
                    opts[i][0] = {0, 0, 100};
                    opts[i][1] = {1, 0, 100};
                    cnt[i] = 2;
                } else if (st == 1) {
                    if (lb == 1) {
                        opts[i][0] = {1, 1, scoreLow(i)};
                        cnt[i] = 1;
                    } else {
                        opts[i][0] = {0, 1, scoreLow(i)};
                        opts[i][1] = {1, 0, 100};
                        cnt[i] = 2;
                    }
                } else if (st == 2) {
                    if (rb == 0) {
                        opts[i][0] = {0, 2, scoreHigh(i)};
                        cnt[i] = 1;
                    } else {
                        opts[i][0] = {1, 2, scoreHigh(i)};
                        opts[i][1] = {0, 0, 100};
                        cnt[i] = 2;
                    }
                } else {
                    if (lb == rb) {
                        opts[i][0] = {lb, 3, -1};
                        cnt[i] = 1;
                    } else {
                        opts[i][0] = {0, 1, scoreLow(i)};
                        opts[i][1] = {1, 2, scoreHigh(i)};
                        cnt[i] = 2;
                    }
                }

                int best = 0;
                for (int k = 1; k < cnt[i]; k++) {
                    if (opts[i][k].score > opts[i][best].score) {
                        best = k;
                    }
                }

                choice[i] = best;
                parity ^= opts[i][best].bit;
            }

            // If parity is zero, flip one variable with minimum score loss.
            if (parity == 0) {
                int bestIdx = -1;
                int bestFlip = -1;
                int bestLoss = INT_MAX;

                for (int i = 0; i < N; i++) {
                    if (cnt[i] < 2) continue;

                    int cur = choice[i];
                    for (int k = 0; k < cnt[i]; k++) {
                        if (k == cur) continue;
                        if (opts[i][k].bit == opts[i][cur].bit) continue;

                        int loss = opts[i][cur].score - opts[i][k].score;
                        if (loss < bestLoss) {
                            bestLoss = loss;
                            bestIdx = i;
                            bestFlip = k;
                        }
                    }
                }

                if (bestIdx != -1) {
                    choice[bestIdx] = bestFlip;
                    parity ^= 1;
                }
            }

            if (parity) {
                ans |= (1LL << b);
            }

            for (int i = 0; i < N; i++) {
                state[i] = opts[i][choice[i]].ns;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
