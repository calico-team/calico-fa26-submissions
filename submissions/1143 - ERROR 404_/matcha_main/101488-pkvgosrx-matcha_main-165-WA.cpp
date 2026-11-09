#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int capacity(ll l, ll r) {
    int best = 0;
    for (int k = 1; k <= 30; ++k) {
        ll sz = 1LL << k;
        ll first = ((l + sz - 1) / sz) * sz;
        if (first + sz - 1 <= r)
            best = k;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<ll> L(n), R(n);

        for (auto &x : L) cin >> x;
        for (auto &x : R) cin >> x;

        ll answer = 0;

        for (int b = 29; b >= 0; --b) {
            ll half = 1LL << b;
            ll full = half << 1;

            int parity = 0;
            vector<int> flexible;

            for (int i = 0; i < n; ++i) {
                ll base = (L[i] / full) * full;
                ll mid = base + half;

                if (R[i] < mid) continue;

                if (L[i] >= mid) {
                    parity ^= 1;
                } else {
                    ll left = mid - L[i];
                    ll right = R[i] - mid + 1;

                    int best = (left >= right ? 0 : 1);
                    parity ^= best;
                    flexible.push_back(i);
                }
            }

            int flip = -1;

            if (parity == 0 && !flexible.empty()) {
                int bestCap = 100;
                ll bestLoss = LLONG_MAX;

                for (int i : flexible) {
                    ll base = (L[i] / full) * full;
                    ll mid = base + half;

                    ll left = mid - L[i];
                    ll right = R[i] - mid + 1;

                    int best = (left >= right ? 0 : 1);

                    ll al, ar;
                    if (best == 0) {
                        al = mid;
                        ar = R[i];
                    } else {
                        al = L[i];
                        ar = mid - 1;
                    }

                    int cap = capacity(al, ar);
                    ll loss = abs(left - right);

                    if (cap < bestCap ||
                        (cap == bestCap && loss < bestLoss)) {
                        bestCap = cap;
                        bestLoss = loss;
                        flip = i;
                    }
                }
            }

            int chosenParity = parity;
            if (flip != -1) chosenParity ^= 1;

            if (chosenParity)
                answer |= half;

            for (int i : flexible) {
                ll base = (L[i] / full) * full;
                ll mid = base + half;

                ll left = mid - L[i];
                ll right = R[i] - mid + 1;

                int best = (left >= right ? 0 : 1);
                int bit = best ^ (i == flip);

                if (bit == 0)
                    R[i] = mid - 1;
                else
                    L[i] = mid;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}