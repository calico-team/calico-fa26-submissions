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
            int st;
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
                    flexs.push_back({i, 0, 1, 0, 2, 1});
                }
            } else if (st == 1) {
                if (lb == 1) {
                    fixed_sum ^= 1;
                    state[i] = 1;
                } else {
                    flexs.push_back({i, 1, 1, 0, 3, 1});
                }
            } else if (st == 2) {
                if (rb == 0) {
                    fixed_sum ^= 0;
                    state[i] = 2;
                } else {
                    flexs.push_back({i, 2, 3, 0, 2, 1});
                }
            } else if (st == 3) {
                flexs.push_back({i, 3, 3, 0, 3, 1});
            }
        }

        int c = flexs.size();
        int chosen_bit = 0;
        vector<int> choices(c, 0);

        if (c == 0) {
            chosen_bit = fixed_sum & 1;
        } else {
            int target_parity = (1 - (fixed_sum & 1)) & 1;
            int flex_sum = 0;
            for (int j = 0; j < c; ++j) {
                if (flexs[j].st == 1) {
                    choices[j] = 1;
                    flex_sum += flexs[j].val1;
                } else {
                    choices[j] = 0;
                    flex_sum += flexs[j].val0;
                }
            }
            if ((flex_sum & 1) != target_parity) {
                choices[0] = 1 - choices[0];
            }
            int total_flex_val = 0;
            for (int j = 0; j < c; ++j) {
                total_flex_val += (choices[j] == 1 ? flexs[j].val1 : flexs[j].val0);
            }
            chosen_bit = (fixed_sum + total_flex_val) & 1;
        }

        if (chosen_bit) {
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