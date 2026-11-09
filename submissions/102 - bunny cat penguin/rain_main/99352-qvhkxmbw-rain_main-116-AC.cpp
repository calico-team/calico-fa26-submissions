#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#define FASTIO std::ios::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL)
using namespace std;

struct Drone {
    int X, Y, Z;
    char D;
};

int main() {
    FASTIO;
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<Drone> drones;
        for (int i = 0; i < N; i++) {
            int X, Y, Z;
            char D;
            cin >> X >> Y >> Z >> D;
            drones.push_back({X, Y, Z, D});
        }

        long long rain_collected = (long long)N * K;
        long long overlap = 0;

        vector<pair<int, int>> east;
        for (int i = 0; i < N; i++) {
            if (drones[i].D == 'E') east.push_back({drones[i].X + drones[i].Y, drones[i].X});
        }
        sort(east.begin(), east.end());

        for (int i = 0; i < N; i++) {
            if (drones[i].D != 'N') continue;
            int s = drones[i].X + drones[i].Y;
            int lo = drones[i].X - (K - 1);
            int hi = drones[i].X - 1;
            auto itLo = lower_bound(east.begin(), east.end(), make_pair(s, lo));
            auto itHi = upper_bound(east.begin(), east.end(), make_pair(s, hi));
            if (itHi > itLo) overlap += itHi - itLo;
        }
        cout << rain_collected - overlap << endl;
    }
    return 0;
}