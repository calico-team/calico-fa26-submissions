#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
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
    vector<pair<int, int>> east, north;
    for (const auto& [x, y, height, direction] : L) {
 
        (direction == 'E' ? east : north).emplace_back(-x - y, -y);
    }
    sort(north.begin(), north.end());

    long long pairs = 0;
    for (const auto& [key, clock] : east) {
        const auto lo = lower_bound(north.begin(), north.end(), make_pair(key, clock));
        const auto hi = lower_bound(lo, north.end(), make_pair(key, clock + K));
        pairs += hi - lo;
    }
    return 1LL * N * K - pairs;
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
