#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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

long long solve(int N, int K, vector<tuple<int, int, int, char>>& L) {

    vector<pair<long long, long long>> east, north;

    for (auto [x, y, z, d] : L) {
        long long diagonal = 1LL * x + y;

        if (d == 'E') {
            east.push_back({diagonal, x});
        } else {
            north.push_back({diagonal, x});
        }
    }

    sort(east.begin(), east.end());
    east.erase(unique(east.begin(), east.end()), east.end());

    sort(north.begin(), north.end());
    north.erase(unique(north.begin(), north.end()), north.end());

    long long ans = 1LL * (east.size() + north.size()) * K;

    for (auto [diagonal, x] : east) {
        pair<long long, long long> low = {diagonal, x};
        pair<long long, long long> high = {diagonal, x + K - 1};

        auto first = lower_bound(north.begin(), north.end(), low);
        auto last = upper_bound(north.begin(), north.end(), high);

        ans -= last - first;
    }

    return ans;
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
