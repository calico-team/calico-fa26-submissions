#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "timer.h"
#else
struct Timer {
    Timer(string_view = "") {}
};
#endif

#ifdef DEBUG
#include "dbg.h"
#else
#define dbg(...) __VA_ARGS__
#endif

void solve() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, vector<pair<int, int>>> N;
    vector<pair<int, int>> e_set;
    e_set.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        if (d == 'E') {
            e_set.push_back({x, y});
        } else {
            N[x + y].push_back({x, y});
        }
    }
    int cnt = 0;
    for (auto& [x1, y1] : e_set) {
        int sq = x1 + y1;
        for (auto& [x2, y2] : N[sq]) {
            if (x1 < x2 && y1 > y2 && x2 - x1 < k) {
                dbg(x1, y1, x2, y2);
                cnt++;
            }
        }
    }
    cout << n * k - cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        dbg("---");
        solve();
    }
    cout << flush;
    return 0;
}
