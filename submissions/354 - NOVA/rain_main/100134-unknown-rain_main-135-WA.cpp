#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int id;
    long long x, y, z;
    char dir;
};

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    vector<Drone> drones(n);
    for (int i = 0; i < n; i++) {
        drones[i].id = i;
        cin >> drones[i].x >> drones[i].y >> drones[i].z >> drones[i].dir;
    }
    vector<vector<pair<long long, long long>>> blocked_intervals(n);
    map<long long, vector<int>> line1_E, line1_N;
    map<long long, vector<int>> line2_N, line2_E;
    for (int i = 0; i < n; i++) {
        if (drones[i].dir == 'E') {
            line1_E[drones[i].y - drones[i].x].push_back(i);
            line2_E[drones[i].y + drones[i].x].push_back(i);
        } else {
            line1_N[drones[i].y - drones[i].x].push_back(i);
            line2_N[drones[i].y + drones[i].x].push_back(i);
        }
    }
    for (auto& [val, vecE] : line1_E) {
        if (!line1_N.count(val)) continue;
        auto& vecN = line1_N[val];
        sort(vecE.begin(), vecE.end(), [&](int a, int b) { return drones[a].x < drones[b].x; });
        sort(vecN.begin(), vecN.end(), [&](int a, int b) { return drones[a].x < drones[b].x; });
        for (int e_idx : vecE) {
            long long x_e = drones[e_idx].x;
            long long z_e = drones[e_idx].z;
            for (int n_idx : vecN) {
                long long x_n = drones[n_idx].x;
                long long z_n = drones[n_idx].z;
                if (x_n >= x_e && x_n <= x_e + k - 1) {
                    if (z_e < z_n) {
                        long long t = x_n - x_e;
                        blocked_intervals[e_idx].push_back({t, t});
                    }
                }
                if (x_n > x_e + k - 1) break; 
            }
        }
        for (int n_idx : vecN) {
            long long x_n = drones[n_idx].x;
            long long z_n = drones[n_idx].z;
            for (int e_idx : vecE) {
                long long x_e = drones[e_idx].x;
                long long z_e = drones[e_idx].z;
                if (x_n >= x_e && x_n <= x_e + k - 1) {
                    if (z_n < z_e) {
                        long long t = x_n - x_e;
                        blocked_intervals[n_idx].push_back({t, t});
                    }
                }
                if (x_e > x_n) break;
            }
        }
    }
    for (auto& [val, vecN] : line2_N) {
        if (!line2_E.count(val)) continue;
        auto& vecE = line2_E[val];
        sort(vecN.begin(), vecN.end(), [&](int a, int b) { return drones[a].y < drones[b].y; });
        sort(vecE.begin(), vecE.end(), [&](int a, int b) { return drones[a].y < drones[b].y; });
        for (int n_idx : vecN) {
            long long y_n = drones[n_idx].y;
            long long z_n = drones[n_idx].z;
            for (int e_idx : vecE) {
                long long y_e = drones[e_idx].y;
                long long z_e = drones[e_idx].z;
                if (y_e >= y_n && y_e <= y_n + k - 1) {
                    if (z_n < z_e) {
                        long long t = y_e - y_n;
                        blocked_intervals[n_idx].push_back({t, t});
                    }
                }
                if (y_e > y_n + k - 1) break;
            }
        }
        for (int e_idx : vecE) {
            long long y_e = drones[e_idx].y;
            long long z_e = drones[e_idx].z;
            for (int n_idx : vecN) {
                long long y_n = drones[n_idx].y;
                long long z_n = drones[n_idx].z;
                if (y_e >= y_n && y_e <= y_n + k - 1) {
                    if (z_e < z_n) {
                        long long t = y_e - y_n;
                        blocked_intervals[e_idx].push_back({t, t});
                    }
                }
                if (y_n > y_e) break;
            }
        }
    }
    long long total_blocked_days = 0;
    for (int i = 0; i < n; i++) {
        if (blocked_intervals[i].empty()) continue;
        auto& ivs = blocked_intervals[i];
        sort(ivs.begin(), ivs.end());
        long long cur_l = ivs[0].first;
        long long cur_r = ivs[0].second;
        for (size_t j = 1; j < ivs.size(); j++) {
            if (ivs[j].first <= cur_r + 1) {
                cur_r = max(cur_r, ivs[j].second);
            } else {
                total_blocked_days += (cur_r - cur_l + 1);
                cur_l = ivs[j].first;
                cur_r = ivs[j].second;
            }
        }
        total_blocked_days += (cur_r - cur_l + 1);
    }
    long long total_collected = 1LL * n * k - total_blocked_days;
    cout << total_collected << endl;
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
