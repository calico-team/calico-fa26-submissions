#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    const int B = 30;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> L(n), R(n);
        for (int i = 0; i < n; i++) {
            cin >> L[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> R[i];
        }
        long long K = 0;
        vector<vector<pair<long long, long long>>> groups(B);
        for (int i = 0; i < n; i++) {
            long long l = L[i], r = R[i];
            if (l == r) {
                K ^= l;
                continue;
            }
            int b = 63 - __builtin_clzll(l ^ r);
            long long mask = (1LL << b) - 1;
            K ^= (l >> (b + 1)) << (b + 1);
            groups[b].push_back({mask - (l & mask), r & mask});
        }
        vector<int> cnt(B, 0);
        long long res = 0;
        for (int j = B - 1; j >= 0; j--) {
            int d = cnt[j];
            int Kj = (K >> j) & 1;
            if (!groups[j].empty()) {
                if (d >= 1) {
                    res |= (1LL << (j + 1)) - 1;
                    break;
                }
                int rho = 1 ^ Kj;
                res |= 1LL << j;
                auto &els = groups[j];
                int v = els.size();
                int n1 = 0;
                for (auto &e : els)
                    if (e.second >= e.first) n1++;
                int o = -1;
                if ((n1 & 1) != rho) {
                    pair<int, long long> bk;
                    for (int i = 0; i < v; i++) {
                        long long a = els[i].first, c = els[i].second;
                        long long x = a ^ c;
                        int t = x ? 64 - __builtin_clzll(x) : 0;
                        pair<int, long long> key = {t, llabs(a - c)};
                        if (o == -1 || key < bk) {
                            bk = key;
                            o = i;
                        }
                    }
                }
                for (int i = 0; i < v; i++) {
                    long long a = els[i].first, c = els[i].second;
                    long long lim = (i == o) ? min(a, c) : max(a, c);
                    for (int k = 0; k < j; k++)
                        if ((lim >> k) & 1) cnt[k]++;
                }
                K ^= (long long)rho << j;
                if ((v + rho) & 1) K ^= (1LL << j) - 1;
            } else {
                if (d >= 2 || (d == 1 && Kj == 1)) {
                    res |= (1LL << (j + 1)) - 1;
                    break;
                } else if (d == 1) {
                    res |= 1LL << j;
                } else {
                    res |= (long long)Kj << j;
                }
            }
        }
        cout << res << "\n";
    }
}
