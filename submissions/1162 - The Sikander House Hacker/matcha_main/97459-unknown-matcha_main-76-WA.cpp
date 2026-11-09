#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<long long> L(n), R(n);
    for (int i = 0; i < n; ++i) cin >> L[i];
    for (int i = 0; i < n; ++i) cin >> R[i];

    vector<int> state(n, 0);
    long long ans = 0;

    for (int b = 29; b >= 0; --b) {
        long long fixed_sum = 0;
        struct Flex {
            int id;
            int next0, val0;
            int next1, val1;
        };
        vector<Flex> flexs;

        for (int i = 0; i < n; ++i) {
            int st = state[i];
            int lb = (L[i] >> b) & 1;
            int rb = (R[i] >> b) & 1;

            if (st == 0) {
                if (lb == rb) {
                    fixed_sum ^= lb;
                    state[i] = 0;
                } else {
                    flexs.push_back({i, 1, 0, 2, 1});
                }
            } else if (st == 1) {
                if (lb == 0) {
                    flexs.push_back({i, 1, 0, 3, 1});
                } else {
                    fixed_sum ^= 1;
                    state[i] = 1;
                }
            } else if (st == 2) {
                if (rb == 0) {
                    fixed_sum ^= 0;
                    state[i] = 2;
                } else {
                    flexs.push_back({i, 3, 0, 2, 1});
                }
            } else if (st == 3) {
                flexs.push_back({i, 3, 0, 3, 1});
            }
        }

        int c = flexs.size();
        int base_xor = fixed_sum & 1;

        int target_bit = 0;
        if (base_xor == 1 || c > 0) {
            target_bit = 1;
        } else {
            target_bit = 0;
        }

        vector<int> choices(c, 0);
        if (target_bit == 1) {
            if (base_xor == 0 && c > 0) {
                choices[0] = 1;
            }
        } else {
            if (base_xor == 1 && c > 0) {
                choices[0] = 1;
            }
        }

        if (target_bit) {
            ans |= (1ULL << b);
        }

        for (int j = 0; j < c; ++j) {
            int id = flexs[j].id;
            if (choices[j] == 1) {
                state[id] = flexs[j].next1;
            } else {
                state[id] = flexs[j].next0;
            }
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