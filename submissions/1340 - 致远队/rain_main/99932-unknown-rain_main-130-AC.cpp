#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Drone {
    long long x, y, z;
    char dir;
};

void solve() {
    int N;
    long long K;
    if (!(cin >> N >> K)) return;

    vector<Drone> drones(N);
    // Map from S = x+y to list of X coordinates for East-moving and North-moving drones
    map<long long, vector<long long>> east_X;
    map<long long, vector<long long>> north_X;

    for (int i = 0; i < N; ++i) {
        cin >> drones[i].x >> drones[i].y >> drones[i].z >> drones[i].dir;
        long long s = drones[i].x + drones[i].y;
        if (drones[i].dir == 'E') {
            east_X[s].push_back(drones[i].x);
        } else {
            north_X[s].push_back(drones[i].x);
        }
    }

    long long total_rain = (long long)N * K;
    long long collisions = 0;
    for (auto& pair : east_X) {
        long long s = pair.first;
        if (north_X.find(s) == north_X.end()) continue;

        vector<long long>& e_vec = pair.second;
        vector<long long>& n_vec = north_X[s];
        sort(e_vec.begin(), e_vec.end());
        sort(n_vec.begin(), n_vec.end());

        for (long long n_x : n_vec) {
            long long min_ex = n_x - K + 1;
            long long max_ex = n_x;

            auto it_low = lower_bound(e_vec.begin(), e_vec.end(), min_ex);
            auto it_high = upper_bound(e_vec.begin(), e_vec.end(), max_ex);

            if (it_low != e_vec.end() && it_low <= it_high) {
                 collisions += (it_high - it_low);
            }
        }
    }
    
    cout << total_rain - collisions << endl;
}

int main() {
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
