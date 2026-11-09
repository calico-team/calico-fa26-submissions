
#include <bits/stdc++.h>
using namespace std;

const int B = 30;
const int MAXVAL = (1 << B) - 1;

using Basis = array<int, B>;

void insertBasis(Basis &basis, int x) {
    for (int b = B - 1; b >= 0 && x; b--) {
        if (!(x & (1 << b))) continue;

        if (!basis[b]) {
            basis[b] = x;
            return;
        }

        x ^= basis[b];
    }
}

void mergeBasis(Basis &a, const Basis &b) {
    for (int i = B - 1; i >= 0; i--) {
        if (b[i]) insertBasis(a, b[i]);
    }
}

int maximize(const Basis &basis, int x, int k) {
    int result = x >> k;

    for (int b = B - 1; b >= k; b--) {
        int v = basis[b] >> k;
        result = max(result, result ^ v);
    }

    long long low = (1LL << k) - 1;
    return (int)(((long long)result << k) | low);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> L(N), R(N);

        for (int &x : L) cin >> x;
        for (int &x : R) cin >> x;

        vector<int> diff(N);
        int base = 0;

        for (int i = 0; i < N; i++) {
            base ^= L[i];
            diff[i] = L[i] ^ R[i];
        }

        vector<Basis> suffix(N + 1);
        suffix[N].fill(0);

        for (int i = N - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1];
            insertBasis(suffix[i], diff[i]);
        }

        Basis prefix{};
        prefix.fill(0);

        int answer = maximize(suffix[0], base, 0);

        for (int i = 0; i < N; i++) {
            if (answer == MAXVAL) break;

            Basis other = prefix;
            mergeBasis(other, suffix[i + 1]);

            int fixed = base ^ L[i];

            long long cur = L[i];

            while (cur <= R[i]) {
                int k;

                if (cur == 0)
                    k = B;
                else
                    k = min(B, __builtin_ctzll(cur));

                while ((1LL << k) > R[i] - cur + 1)
                    k--;

                int candidate = maximize(
                    other, fixed ^ (int)cur, k
                );

                answer = max(answer, candidate);

                cur += 1LL << k;
            }

            insertBasis(prefix, diff[i]);
        }

        cout << answer << '\n';
    }
}
