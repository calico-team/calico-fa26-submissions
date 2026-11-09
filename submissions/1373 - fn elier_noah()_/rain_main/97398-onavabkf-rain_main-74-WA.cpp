#include <vector>
#include <iostream>

using namespace std;

/*
* Return an integer denoting the amount of rain collected after the Kth nights
* 
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
*/

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    long long answer = 0;

    for (int i = 0; i < K; ++i) {
        // night loop

        for (int j = 0; j < N; ++j) {
            // move everyone
            auto [X, Y, Z, D] = L[j];
            if (D == 'N') {
                Y++;
            } else if (D == 'S') {
                Y--;
            } else if (D == 'E') {
                X++;
            } else if (D == 'W') {
                X--;
            }

            L[j] = {X, Y, Z, D};
        }

        for (int j = 0; j < N; ++j) {
            // check if we get water tonight
            auto [X, Y, Z, D] = L[j];
            bool is_above = false;
            for (int m = 0; m < N; ++m) {
                // 2nd drone loop; searching
                auto [LX, LY, LZ, _] = L[m];
                if (LX == X && LY == Y && LZ > Z) {
                    is_above = true;
                    break;
                }
            }

            if (!is_above) {
                answer++;
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}
