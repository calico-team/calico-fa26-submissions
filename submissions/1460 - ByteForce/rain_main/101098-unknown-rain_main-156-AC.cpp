#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Drone {
    long long diag; // x + y
    long long x;
    char dir;
};

void solve() {
    long long n, k;
    if (!(cin >> n >> k)) return;

    vector<Drone> east_drones;
    vector<Drone> north_drones;
    east_drones.reserve(n);
    north_drones.reserve(n);

    for (long long i = 0; i < n; ++i) {
        long long x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        if (d == 'E') {
            east_drones.push_back({x + y, x, d});
        } else {
            north_drones.push_back({x + y, x, d});
        }
    }

    long long total = n * k;
    if (k <= 1 || east_drones.empty() || north_drones.empty()) {
        cout << total << '\n';
        return;
    }

    auto cmp = [](const Drone& a, const Drone& b) {
        if (a.diag != b.diag) return a.diag < b.diag;
        return a.x < b.x;
    };

    sort(east_drones.begin(), east_drones.end(), cmp);
    sort(north_drones.begin(), north_drones.end(), cmp);

    long long blocked = 0;
    size_t i = 0, j = 0;
    while (i < east_drones.size() && j < north_drones.size()) {
        if (east_drones[i].diag < north_drones[j].diag) {
            ++i;
        } else if (east_drones[i].diag > north_drones[j].diag) {
            ++j;
        } else {
            long long d = east_drones[i].diag;
            size_t i_end = i;
            while (i_end < east_drones.size() && east_drones[i_end].diag == d) {
                ++i_end;
            }
            size_t j_end = j;
            while (j_end < north_drones.size() && north_drones[j_end].diag == d) {
                ++j_end;
            }

            // Two-pointer sliding window on sorted x-coordinates for this diagonal
            size_t left = j, right = j;
            for (size_t p = i; p < i_end; ++p) {
                long long lo = east_drones[p].x + 1;
                long long hi = east_drones[p].x + k - 1;
                while (left < j_end && north_drones[left].x < lo) {
                    ++left;
                }
                if (right < left) right = left;
                while (right < j_end && north_drones[right].x <= hi) {
                    ++right;
                }
                blocked += static_cast<long long>(right - left);
            }

            i = i_end;
            j = j_end;
        }
    }

    cout << (total - blocked) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
