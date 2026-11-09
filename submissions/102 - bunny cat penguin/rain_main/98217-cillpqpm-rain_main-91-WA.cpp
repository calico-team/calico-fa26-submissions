#include <iostream>
#include <vector>
#define FASTIO std::ios::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL)
using namespace std;

int main() { FASTIO;
    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        vector<pair<int, int>> north_drones;
        vector<pair<int, int>> east_drones;
        for (int i = 0; i < N; i++) {
            int X, Y, Z; char D; cin >> X >> Y >> Z >> D;
            if (D == 'N') north_drones.push_back({X, Y});
            if (D == 'E') east_drones.push_back({X, Y});
        }

        long long rain_collected = N * K;
        for (auto n : north_drones) {
            for (auto e : east_drones) {
                if (n.first > e.first && n.second < e.second) {
                    if (n.first - e.first == e.second - n.second && n.first - e.first < K) {
                        rain_collected--;
                    }
                }
            }
        }
        cout << rain_collected << endl;
    }
    return 0;
}