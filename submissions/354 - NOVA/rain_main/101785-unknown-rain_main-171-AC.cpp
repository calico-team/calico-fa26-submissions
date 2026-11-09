#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    map<long long, vector<long long>> line_E, line_N;
    for (int i = 0; i < n; i++) {
        long long x, y, z;
        char dir;
        cin >> x >> y >> z >> dir;
        long long key = x + y;
        if (dir == 'E') {
            line_E[key].push_back(x);
        } else {
            line_N[key].push_back(x);
        }
    }
    long long total_blocked_days = 0;
    for (auto& [val, vecE] : line_E) {
        if (!line_N.count(val)) continue;
        auto& vecN = line_N[val];
        sort(vecN.begin(), vecN.end());
        for (long long x_e : vecE) {
            auto l = lower_bound(vecN.begin(), vecN.end(), x_e);
            auto r = upper_bound(vecN.begin(), vecN.end(), x_e + k - 1);
            total_blocked_days += (r - l);
        }
    }
    long long total_collected = 1LL * n * k - total_blocked_days;
    cout << total_collected << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
