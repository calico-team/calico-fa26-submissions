#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct Drone {
    int diagonal, x;
    char direction;

    bool operator<(const Drone& other) const {
        return tie(diagonal, x) < tie(other.diagonal, other.x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, nights;
        cin >> n >> nights;
        vector<Drone> drones(n);
        for (auto& drone : drones) {
            int y, height;
            cin >> drone.x >> y >> height >> drone.direction;
            drone.diagonal = drone.x + y;
        }
        sort(drones.begin(), drones.end());

        long long total = 1LL * n * nights;
        int left = 0, east = 0;
        for (int i = 0; i < n; ++i) {
            const auto& drone = drones[i];
            while (left < i && (drones[left].diagonal != drone.diagonal ||
                                drone.x - drones[left].x >= nights)) {
                east -= drones[left].direction == 'E';
                ++left;
            }
            if (drone.direction == 'E')
                ++east;
            else
                total -= east;
        }
        cout << total << '\n';
    }
}
