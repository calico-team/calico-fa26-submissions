#include <bits/stdc++.h>
using namespace std;

struct Drone {
    long long x, y, z;
    char d;
};

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<Drone> drones(n);
    for (int i = 0; i < n; i++) {
        cin >> drones[i].x >> drones[i].y >> drones[i].z >> drones[i].d;
    }

    long long total_rain = (long long)n * k;

    for (int i = 0; i < n; i++) {
        bool permanently_blocked = false;
        set<long long> blocked_nights;

        for (int j = 0; j < n; j++) {
            if (drones[j].z <= drones[i].z) continue;

            if (drones[i].d == drones[j].d) {
                if (drones[i].x == drones[j].x && drones[i].y == drones[j].y) {
                    permanently_blocked = true;
                    break;
                }
            } else {
                if (drones[i].d == 'E' && drones[j].d == 'N') {
                    long long dx = drones[j].x - drones[i].x;
                    long long dy = drones[i].y - drones[j].y;
                    if (dx == dy && dx >= 0 && dx < k) {
                        blocked_nights.insert(dx + 1);
                    }
                }
                else if (drones[i].d == 'N' && drones[j].d == 'E') {
                    long long dx = drones[i].x - drones[j].x;
                    long long dy = drones[j].y - drones[i].y;
                    if (dx == dy && dx >= 0 && dx < k) {
                        blocked_nights.insert(dx + 1);
                    }
                }
            }
        }

        if (permanently_blocked) {
            total_rain -= k;
        } else {
            total_rain -= blocked_nights.size();
        }
    }

    cout << total_rain << "\n";
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