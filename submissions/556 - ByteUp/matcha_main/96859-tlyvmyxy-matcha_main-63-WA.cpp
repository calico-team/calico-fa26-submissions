#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    if (!(cin >> N)) return;

    vector<long long> L(N), R(N);
    for (int i = 0; i < N; ++i) cin >> L[i];
    for (int i = 0; i < N; ++i) cin >> R[i];

    long long cur_min = 0, cur_max = 0;

    for (int i = 0; i < N; ++i) {
        long long l = L[i], r = R[i];
        
        // Find the highest bit where L_i and R_i differ
        int diff_bit = -1;
        for (int b = 29; b >= 0; --b) {
            if (((l >> b) & 1) != ((r >> b) & 1)) {
                diff_bit = b;
                break;
            }
        }

        if (diff_bit == -1) {
            // L_i == R_i: exact single value choice
            long long n1 = cur_min ^ l;
            long long n2 = cur_max ^ l;
            cur_min = min(n1, n2);
            cur_max = max(n1, n2);
        } else {
            // Range spans both 0 and 1 at diff_bit
            long long mask = (1LL << (diff_bit + 1)) - 1;
            long long prefix_l = l & ~mask;

            long long n1 = cur_min ^ prefix_l;
            long long n2 = cur_max ^ prefix_l;
            
            // Expand reachable bounds with full lower bit coverage
            long long base_min = min(n1, n2) & ~mask;
            long long base_max = max(n1, n2) | mask;

            cur_min = base_min;
            cur_max = base_max;
        }
    }

    cout << cur_max << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
