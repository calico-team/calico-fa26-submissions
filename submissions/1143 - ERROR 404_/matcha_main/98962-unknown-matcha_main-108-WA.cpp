#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int type; // 0: forced 0, 1: forced 1, 2: flexible
    int id;
    int delta;
    bool nxt_tl_0, nxt_tr_0;
    bool nxt_tl_1, nxt_tr_1;
};

void solve() {
    int N;
    if (!(cin >> N)) return;
    vector<long long> L(N), R(N);
    for (int i = 0; i < N; ++i) cin >> L[i];
    for (int i = 0; i < N; ++i) cin >> R[i];

    vector<bool> T_L(N, true);
    vector<bool> T_R(N, true);

    long long ans = 0;
    for (int b = 29; b >= 0; --b) {
        int c0 = 0, c1 = 0;
        vector<Item> flex;
        vector<Item> flex_items;

        for (int i = 0; i < N; ++i) {
            int lb = (L[i] >> b) & 1;
            int rb = (R[i] >> b) & 1;
            bool tl = T_L[i];
            bool tr = T_R[i];

            bool valid_0 = true, valid_1 = true;
            if (tl && lb == 1) valid_0 = false;
            if (tr && rb == 0) valid_1 = false;

            if (valid_0 && !valid_1) {
                c0++;
                bool nxt_tl = tl && (0 == lb);
                bool nxt_tr = tr && (0 == rb);
                flex.push_back({0, i, 0, nxt_tl, nxt_tr, nxt_tl, nxt_tr});
            } else if (!valid_0 && valid_1) {
                c1++;
                bool nxt_tl = tl && (1 == lb);
                bool nxt_tr = tr && (1 == rb);
                flex.push_back({1, i, 0, nxt_tl, nxt_tr, nxt_tl, nxt_tr});
            } else {
                bool nxt_tl_0 = tl && (0 == lb);
                bool nxt_tr_0 = tr && (0 == rb);
                int score_0 = (!nxt_tl_0 && !nxt_tr_0) ? 0 : ((!nxt_tl_0 || !nxt_tr_0) ? 1 : 2);

                bool nxt_tl_1 = tl && (1 == lb);
                bool nxt_tr_1 = tr && (1 == rb);
                int score_1 = (!nxt_tl_1 && !nxt_tr_1) ? 0 : ((!nxt_tl_1 || !nxt_tr_1) ? 1 : 2);

                int delta = score_1 - score_0;
                flex.push_back({2, i, delta, nxt_tl_0, nxt_tr_0, nxt_tl_1, nxt_tr_1});
                flex_items.push_back(flex.back());
            }
        }

        int forced1_count = c1;
        int k = flex_items.size();

        sort(flex_items.begin(), flex_items.end(), [](const Item& a, const Item& b) {
            return a.delta < b.delta;
        });

        int min_ones = forced1_count;
        int max_ones = forced1_count + k;
        bool odd_exists = (min_ones % 2 != 0) || (max_ones % 2 != 0) || (min_ones != max_ones);

        int chosen_x = 0;
        int desired_x_parity = odd_exists ? (1 - forced1_count % 2 + 2) % 2 : (0 - forced1_count % 2 + 2) % 2;

        int opt_x = 0;
        for (const auto& item : flex_items) {
            if (item.delta < 0) opt_x++;
        }
        opt_x = max(0, min(k, opt_x));

        vector<int> candidates;
        for (int x_val : {opt_x - 1, opt_x, opt_x + 1, opt_x - 2, opt_x + 2, 0, k}) {
            if (x_val >= 0 && x_val <= k && (x_val % 2 == desired_x_parity)) {
                candidates.push_back(x_val);
            }
        }

        vector<long long> pref(k + 1, 0);
        for (int i = 0; i < k; ++i) {
            pref[i + 1] = pref[i] + flex_items[i].delta;
        }

        long long best_cost = 1e18;
        int best_x = 0;
        for (int x_val : candidates) {
            long long cost = pref[x_val];
            if (cost < best_cost) {
                best_cost = cost;
                best_x = x_val;
            }
        }

        chosen_x = best_x;
        if (odd_exists) {
            ans = (ans << 1) | 1;
        } else {
            ans = (ans << 1) | 0;
        }

        for (const auto& item : flex) {
            if (item.type != 2) {
                T_L[item.id] = item.nxt_tl_0;
                T_R[item.id] = item.nxt_tr_0;
            }
        }

        for (int idx_flex = 0; idx_flex < k; ++idx_flex) {
            const auto& item = flex_items[idx_flex];
            if (idx_flex < chosen_x) {
                T_L[item.id] = item.nxt_tl_1;
                T_R[item.id] = item.nxt_tr_1;
            } else {
                T_L[item.id] = item.nxt_tl_0;
                T_R[item.id] = item.nxt_tr_0;
            }
        }
    }

    cout << ans << "\n";
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
