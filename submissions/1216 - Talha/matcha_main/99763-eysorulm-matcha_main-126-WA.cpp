#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int N, vector<int> L, vector<int> R) {
    if (N == 1) return R[0];

    int max_diff_bit = -1;
    for (int i = 0; i < N; i++) {
        if (L[i] != R[i]) {
            int diff = L[i] ^ R[i];
            int b = 31 - __builtin_clz(diff);
            max_diff_bit = max(max_diff_bit, b);
        }
    }

    if (max_diff_bit == -1) {
        int res = 0;
        for (int x : L) res ^= x;
        return res;
    }

    int fixed_xor = 0;
    for (int i = 0; i < N; i++) {
        fixed_xor ^= (L[i] >> (max_diff_bit + 1)) << (max_diff_bit + 1);
    }
    return fixed_xor | ((1 << (max_diff_bit + 1)) - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N; cin >> N;
        vector<int> L(N), R(N);
        for (int& i : L) cin >> i;
        for (int& i : R) cin >> i;
        cout << solve(N, L, R) << '\n';
    }
    return 0;
}