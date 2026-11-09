#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<long long> L(n), R(n);
    for (int i = 0; i < n; ++i) cin >> L[i];
    for (int i = 0; i < n; ++i) cin >> R[i];

    long long ans = 0;

    for (int b = 29; b >= 0; --b) {
        long long min_xor = 0;
        long long max_xor = 0;

        for (int i = 0; i < n; ++i) {
            long long l_pref = L[i] >> (b + 1);
            long long r_pref = R[i] >> (b + 1);
            long long l_bit = (L[i] >> b) & 1;
            long long r_bit = (R[i] >> b) & 1;

            if (l_pref < r_pref) {
                min_xor ^= 0;
                max_xor ^= 1;
            } else {
                long long bit_val = l_bit;
                min_xor ^= bit_val;
                max_xor ^= bit_val;
            }
        }

        if (max_xor == 1) {
            ans |= (1ULL << b);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}