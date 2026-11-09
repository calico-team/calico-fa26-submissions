#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <tuple>

using namespace std;

/*
* Return an integer denoting the amount of rain collected after the Kth nights
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] afor each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
*/

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    long long answer = 0;

    unordered_map<long long, int> tallest;
    tallest.reserve(N);

    for (int i = 0; i < K; ++i) {
        // night loop
        tallest.clear();

        // tallest in each cell
        for (int j = 0; j < N; ++j) {
            auto [X, Y, Z, D] = L[j];
            long long key = X | (static_cast<long long>(Y) << 32ULL);
            tallest[key] = max(tallest[key], Z);
        }

        // get water if you're the tallest
        for (int j = 0; j < N; ++j) {
            auto [X, Y, Z, D] = L[j];
            long long key = X | (static_cast<long long>(Y) << 32ULL);
            if (Z == tallest[key]) answer++;
        }

        // move everyone
        for (int j = 0; j < N; ++j) {
            auto [X, Y, Z, D] = L[j];
            if (D == 'N') {
                Y++;
            } else if (D == 'E') {
                X++;
            }

            L[j] = {X, Y, Z, D};
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
