#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void solve() {
    int n; long long k; cin >> n >> k;
    
    vector<pair<long long, long long>> east_drones; vector<pair<long long, long long>> north_drones;
    
    for (int i = 0; i < n; i++) {
        long long x, y, z; char d; cin >> x >> y >> z >> d;
        if (d == 'E') {
            east_drones.push_back({x + y, x});
        } else {
            north_drones.push_back({x + y, x});
        }
    }
    
    map<long long, vector<long long>> north_map;
    for (auto& drone : north_drones) {
        north_map[drone.first].push_back(drone.second);
    }
    
    for (auto& pair_item : north_map) {
        sort(pair_item.second.begin(), pair_item.second.end());
    }
    
    long long collisions = 0;
    
    for (auto& drone : east_drones) {
        long long sum_xy = drone.first; long long x_i = drone.second;
        
        if (north_map.find(sum_xy) != north_map.end()) {
            auto& x_coords = north_map[sum_xy]; auto it1 = lower_bound(x_coords.begin(), x_coords.end(), x_i); auto it2 = lower_bound(x_coords.begin(), x_coords.end(), x_i + k);
            collisions += distance(it1, it2);
        }
    }
    
    long long ans = n * k - collisions; cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}