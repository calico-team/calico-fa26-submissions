#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static ll find_max_xor_sum(const vector<ll>& option_a, const vector<ll>& option_b, int bit_len, int target_parity) {
    int total_items = option_a.size();
    vector<char> is_committed(total_items, 0);
    vector<ll> assigned_val(total_items, 0);
    int free_count = total_items;
    int current_parity = 0;
    ll prefix_max_y = 0;

    for (int t = bit_len - 1; t >= 0; t--) {
        if (free_count <= 2) {
            break;
        }

        int active_count = 0;
        int last_index = -1;

        for (int i = 0; i < total_items; i++) {
            int bit_val = 0;
            if (is_committed[i]) {
                bit_val = (assigned_val[i] >> t) & 1;
            } else {
                bit_val = ((option_a[i] | option_b[i]) >> t) & 1;
            }

            if (bit_val) {
                active_count++;
                last_index = i;
                if (active_count >= 2) {
                    break;
                }
            }
        }

        if (active_count >= 2) {
            return prefix_max_y | ((1LL << (t + 1)) - 1);
        }

        if (active_count == 1) {
            prefix_max_y |= (1LL << t);
            if (!is_committed[last_index]) {
                int bit_a = (option_a[last_index] >> t) & 1;
                int bit_b = (option_b[last_index] >> t) & 1;

                if (!(bit_a && bit_b)) {
                    is_committed[last_index] = 1;
                    if (bit_a) {
                        assigned_val[last_index] = option_a[last_index];
                        current_parity ^= 1;
                    } else {
                        assigned_val[last_index] = option_b[last_index];
                    }
                    free_count--;
                }
            }
        }
    }

    if (free_count >= 3) {
        return prefix_max_y;
    }

    vector<int> uncommitted_indices;
    vector<int> bit_counts(bit_len > 0 ? bit_len : 1, 0);

    for (int i = 0; i < total_items; i++) {
        if (is_committed[i]) {
            for (int t = 0; t < bit_len; t++) {
                bit_counts[t] += (assigned_val[i] >> t) & 1;
            }
        } else {
            uncommitted_indices.push_back(i);
        }
    }

    int uncommitted_size = uncommitted_indices.size();
    ll best_result = -1;

    for (int mask = 0; mask < (1 << uncommitted_size); mask++) {
        int parity_check = current_parity ^ (__builtin_popcount(mask) & 1);
        if (parity_check != (target_parity & 1)) {
            continue;
        }

        vector<int> temp_counts = bit_counts;
        for (int j = 0; j < uncommitted_size; j++) {
            ll val = ((mask >> j) & 1) ? option_a[uncommitted_indices[j]] : option_b[uncommitted_indices[j]];
            for (int t = 0; t < bit_len; t++) {
                temp_counts[t] += (val >> t) & 1;
            }
        }

        ll current_y = 0;
        bool has_collision = false;

        for (int t = bit_len - 1; t >= 0; t--) {
            if (has_collision) {
                current_y |= (1LL << t);
            } else if (temp_counts[t] >= 2) {
                has_collision = true;
                current_y |= (1LL << t);
            } else if (temp_counts[t] == 1) {
                current_y |= (1LL << t);
            }
        }

        best_result = max(best_result, current_y);
    }

    return best_result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        int n;
        cin >> n;

        vector<ll> lower_bounds(n), upper_bounds(n);
        for (auto& x : lower_bounds) cin >> x;
        for (auto& x : upper_bounds) cin >> x;

        vector<pair<ll, ll>> intervals(n);
        for (int i = 0; i < n; i++) {
            intervals[i] = {lower_bounds[i], upper_bounds[i]};
        }

        ll total_ans = 0;

        for (int bit = 29; bit >= 0; bit--) {
            ll full_mask = 1LL << bit;
            int parity_flip = 0;
            vector<pair<ll, ll>> next_intervals;
            next_intervals.reserve(intervals.size() + 2);

            vector<ll> option_a, option_b;

            for (auto& interval : intervals) {
                ll l = interval.first;
                ll r = interval.second;
                int lb = (l >> bit) & 1;
                int rb = (r >> bit) & 1;

                if (lb == 1) {
                    parity_flip ^= 1;
                    next_intervals.push_back({l - full_mask, r - full_mask});
                } else if (rb == 0) {
                    next_intervals.push_back({l, r});
                } else {
                    option_a.push_back(r - full_mask);
                    option_b.push_back((full_mask - 1) - l);
                }
            }

            if (option_a.empty()) {
                if (parity_flip) {
                    total_ans |= full_mask;
                }
                intervals.swap(next_intervals);
                continue;
            }

            total_ans |= full_mask;
            int target_q = 1 ^ parity_flip;
            int k = option_a.size();

            ll computed_y = find_max_xor_sum(option_a, option_b, bit, target_q);
            ll computed_k = (((k - target_q) & 1) ? (full_mask - 1) : 0);

            if (computed_y > 0) {
                next_intervals.push_back({0, computed_y});
            }
            if (computed_k > 0) {
                next_intervals.push_back({computed_k, computed_k});
            }

            intervals.swap(next_intervals);
        }

        cout << total_ans << "\n";
    }

    return 0;
}