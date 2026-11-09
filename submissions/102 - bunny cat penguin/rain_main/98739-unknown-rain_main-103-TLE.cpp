#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
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

        long long rain_collected = (long long) N * K;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                Drone drone1 = drones[i];
                Drone drone2 = drones[j];
                if (drone1.D != drone2.D) {
                    if (drone1.D == 'N') {
                        drone1 = drones[j];
                        drone2 = drones[i];
                    }
                    if (drone1.X < drone2.X && drone1.Y > drone2.Y) {
                        if (drone2.X - drone1.X == drone1.Y - drone2.Y && drone2.X - drone1.X < K)
                            rain_collected--;
                    }
                }
            }
        }
        cout << rain_collected << endl;
    }
    return 0;
}