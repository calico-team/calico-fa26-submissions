// CALICO Fall '26 - Problem 11: A Matcha a Day
// Reads from stdin (input), writes to stdout (output).
#include <bits/stdc++.h>
using namespace std;

// Max XOR of prefix ranges [0,Y_i]: OR of all Y, with every bit at/below the
// highest bit shared by >= 2 values set to 1.
static long long calcX(const int* cnt, int K) {
    long long orv = 0; int g = -1;
    for (int b = 0; b < K; b++) {
        if (cnt[b] >= 1) orv |= 1LL << b;
        if (cnt[b] >= 2) g = b;
    }
    if (g >= 0) orv |= (1LL << (g + 1)) - 1;
    return orv;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        vector<long long> L(n), R(n);
        for (auto &x : L) scanf("%lld", &x);
        for (auto &x : R) scanf("%lld", &x);

        long long C = 0;                           // constant (already decided) part of the XOR
        vector<vector<pair<long long,long long>>> bucket(31);
        for (int i = 0; i < n; i++) {
            if (L[i] == R[i]) { C ^= L[i]; continue; }
            int K = 63 - __builtin_clzll(L[i] ^ R[i]);   // highest differing bit
            C ^= (L[i] >> (K + 1)) << (K + 1);           // shared prefix is constant
            long long M = (1LL << K) - 1;
            long long lo = L[i] & M, hi = R[i] & M;
            bucket[K].push_back({M - lo, hi});           // (a,b): limits for side 0 / side 1
        }

        for (int K = 30; K >= 0; K--) {
            auto &v = bucket[K];
            if (v.empty()) continue;
            int m = v.size();
            long long M = (1LL << K) - 1;
            int p = 1 ^ (int)((C >> K) & 1);             // want bit K of answer = 1

            int cnt[31] = {0};
            int q = 0;
            for (auto &pr : v) {
                long long H = max(pr.first, pr.second);
                q ^= (pr.second > pr.first);
                for (int b = 0; b < K; b++) cnt[b] += (H >> b) & 1;
            }
            long long X;
            if (q == p) X = calcX(cnt, K);
            else {                                       // must flip exactly one number
                X = 0;
                for (auto &pr : v) {
                    long long H = max(pr.first, pr.second), Lo = min(pr.first, pr.second);
                    int c2[31];
                    for (int b = 0; b < K; b++)
                        c2[b] = cnt[b] - (int)((H >> b) & 1) + (int)((Lo >> b) & 1);
                    X = max(X, calcX(c2, K));
                }
            }
            C ^= ((long long)p << K) ^ (((m - p) & 1) ? M : 0);
            if (X > 0) {
                int k = 63 - __builtin_clzll(X);
                bucket[k].push_back({(1LL << k) - 1, X - (1LL << k)});
            }
        }
        printf("%lld\n", C);
    }
    return 0;
}
