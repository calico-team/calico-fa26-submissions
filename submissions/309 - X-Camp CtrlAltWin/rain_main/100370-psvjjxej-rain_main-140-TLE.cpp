#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int t = 0; t < n; ++t) {
        long long count = 0;
        int drones, nights;
        cin >> drones >> nights;

        struct Drone {
            long long x, y, z;
            string d;
        };
        vector<Drone> drone_stuff(drones);
        string d;  // Python's `d` persists as the last drone's direction
        for (int i = 0; i < drones; ++i) {
            long long x, y, z;
            cin >> x >> y >> z >> d;
            drone_stuff[i] = Drone{x, y, z, d};
        }

        long long num = 0;
        for (int i = 0; i < nights; ++i) {
            for (int j = 0; j < drones; ++j) {
                if (d == "N") {
                    drone_stuff[j].y = drone_stuff[j].y - 1;
                } else if (d == "E") {
                    drone_stuff[j].x = drone_stuff[j].x + 1;
                }

                // Build unordered pairs (frozenset semantics) and count distinct ones
                set<pair<long long, long long>> other_counted;
                for (const auto& l : drone_stuff) {
                    long long a = l.x, b = l.y;
                    if (a > b) swap(a, b);
                    other_counted.insert({a, b});
                }
                num = (long long)drone_stuff.size() - (long long)other_counted.size();
            }
            for (int k = 0; k < drones; ++k) {
                count += 1;
            }
            count -= num;
        }
        cout << count << "\n";
    }
    return 0;
}
