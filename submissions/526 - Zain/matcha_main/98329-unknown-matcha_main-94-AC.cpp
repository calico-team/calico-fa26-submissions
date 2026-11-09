#include <bits/stdc++.h>
using namespace std;

struct XorBasis {
    int pivot[30]{};
    int rank = 0;

    void add(int x) {
        while (x) {
            int bit = 31 - __builtin_clz((unsigned)x);
            if (!pivot[bit]) {
                pivot[bit] = x;
                ++rank;
                return;
            }
            x ^= pivot[bit];
        }
    }

    int maximize(int x) const {
        for (int bit = 29; bit >= 0; --bit) {
            if ((x ^ pivot[bit]) > x)
                x ^= pivot[bit];
        }
        return x;
    }
};

struct Candidate {
    int index;
    int options;  // bit 0: L is eligible; bit 1: R is eligible
    int delta;
};

int solve(const vector<int>& L, const vector<int>& R) {
    const int n = (int)L.size();
    vector<int> delta(n);
    int fixedXor = 0;
    XorBasis all;

    for (int i = 0; i < n; ++i) {
        fixedXor ^= L[i];
        delta[i] = L[i] ^ R[i];
        all.add(delta[i]);
    }

    int answer = all.maximize(fixedXor); // All flavors are endpoints.
    if (answer == (1 << 30) - 1)
        return answer;

    vector<int> marked(n, -1);
    vector<Candidate> eligible;
    eligible.reserve(n);

    for (int bit = 28; bit >= 0; --bit) {
        eligible.clear();

        for (int i = 0; i < n; ++i) {
            if ((L[i] >> (bit + 1)) == (R[i] >> (bit + 1)))
                continue;

            int choices = ((L[i] & (1 << bit)) == 0 ? 1 : 0)
                        | ((R[i] & (1 << bit)) != 0 ? 2 : 0);

            if (choices) {
                eligible.push_back({i, choices, delta[i] >> bit});
                marked[i] = bit;
            }
        }

        int k = (int)eligible.size();
        if (k == 0) continue;

        XorBasis projected;
        for (int v : all.pivot)
            projected.add(v >> bit);
        int r = projected.rank;
        int lowMask = (1 << bit) - 1;
        int base = fixedXor >> bit;

        // With enough eligible intervals, any endpoint XOR can
        // be realized with at least two eligible endpoint choices.
        if (k >= r + 2) {
            XorBasis upper;
            for (int v : all.pivot)
                upper.add(v >> (bit + 1));

            int bestHigh = upper.maximize(fixedXor >> (bit + 1));
            answer = max(answer, (bestHigh << (bit + 1)) |
                                 ((1 << (bit + 1)) - 1));
            if (answer == (1 << 30) - 1) return answer;
            continue;
        }

        // Any endpoint XOR can be represented with at least
        // one eligible endpoint choice if k >= rank + 1.
        bool unrestrictedOdd = (k >= r + 1);
        if (unrestrictedOdd) {
            int best = projected.maximize(base ^ 1);
            answer = max(answer, (best << bit) | lowMask);
        }

        // Build the basis from noneligible intervals only.
        XorBasis others;
        for (int i = 0; i < n; ++i) {
            if (marked[i] != bit)
                others.add(delta[i] >> bit);
        }

        // Exactly one interval enters its interior at this bit.
        if (!unrestrictedOdd) {
            for (int a = 0; a < k; ++a) {
                XorBasis basis = others;
                for (int j = 0; j < k; ++j)
                    if (j != a) basis.add(eligible[j].delta);

                const auto &e = eligible[a];
                if (e.options & 1) {
                    int best = basis.maximize(base ^ 1);
                    answer = max(answer, (best << bit) | lowMask);
                }
                if (e.options & 2) {
                    int best = basis.maximize(base ^ e.delta ^ 1);
                    answer = max(answer, (best << bit) | lowMask);
                }
            }
        }

        // Exactly two intervals enter their interiors at this bit.
        // Their bit flips cancel, but we gain full freedom below it.
        for (int a = 0; a < k; ++a) {
            for (int b = a + 1; b < k; ++b) {
                XorBasis basis = others;
                for (int j = 0; j < k; ++j)
                    if (j != a && j != b)
                        basis.add(eligible[j].delta);

                const auto &u = eligible[a];
                const auto &v = eligible[b];
                for (int sideU = 0; sideU <= 1; ++sideU) {
                    if (!(u.options & (1 << sideU))) continue;
                    for (int sideV = 0; sideV <= 1; ++sideV) {
                        if (!(v.options & (1 << sideV))) continue;
                        int start = base ^ (sideU ? u.delta : 0)
                                         ^ (sideV ? v.delta : 0);
                        int best = basis.maximize(start);
                        answer = max(answer, (best << bit) | lowMask);
                    }
                }
            }
        }
        if (answer == (1 << 30) - 1) return answer;
    }
    return answer;
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
        cout << solve(L, R) << '\n';
    }
    return 0;
}
