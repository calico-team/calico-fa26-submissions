#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<long long> L(N), R(N);
    for (int i = 0; i < N; ++i) cin >> L[i];
    for (int i = 0; i < N; ++i) cin >> R[i];

    long long ans = 0;

    // For each bit position from bit 29 down to 0:
    for (int b = 29; b >= 0; --b) {
        long long target = ans | (1LL << b);
        
        // Check if `target` prefix is achievable across all N choices
        long long mask = ~((1LL << b) - 1);
        
        // Compute reachable XOR interval [min_xor, max_xor] masked by upper bits
        long long cur_min = 0, cur_max = 0;
        
        for (int i = 0; i < N; ++i) {
            long long l = L[i], r = R[i];
            
            // Range of values available at step i
            if ((l >> b) != (r >> b)) {
                // If L[i] and R[i] differ at or above bit b, we can pick any bit value for bit b
                long long nxt_min = min(cur_min ^ (l & mask), cur_min ^ (r & mask));
                long long nxt_max = max(cur_max ^ (l & mask), cur_max ^ (r & mask));
                
                // Since L[i] and R[i] differ at bit > b or bit b, 
                // bit b can be set to either 0 or 1 freely.
                cur_min = 0; 
                cur_max = (1LL << 30) - 1;
                break;
            } else {
                long long val = l & mask;
                long long n1 = cur_min ^ val;
                long long n2 = cur_max ^ val;
                cur_min = min(n1, n2);
                cur_max = max(n1, n2);
            }
        }
    }

    // Direct optimal approach:
    // For each day i, range [L_i, R_i] allows choosing a number.
    // The maximum XOR sum across all positions:
    long long res = 0;
    long long fixed_xor = 0;

    for (int b = 29; b >= 0; --b) {
        bool flexible = false;
        long long forced_bit = 0;
        for (int i = 0; i < N; ++i) {
            if ((L[i] >> b) != (R[i] >> b)) {
                flexible = true;
            } else {
                forced_bit ^= ((L[i] >> b) & 1);
            }
        }

        if (flexible) {
            res |= (1LL << b);
        } else {
            res |= (forced_bit << b);
        }
    }

    cout << res << "\n";
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
