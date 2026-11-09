#include <bits/stdc++.h>
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
    map<int, vector<int>> east, north;

    for (int i = 0; i < N; i++) {
        int x = get<0>(L[i]);
        int y = get<1>(L[i]);
        int z = get<2>(L[i]);
        char d = get<3>(L[i]);

        if (d == 'E') {
            east[x + y].push_back(x);
        } else {
            north[x + y].push_back(x);
        }
    }
    answer = 1 * N * K;

    for (auto &[key, E] : east) {
        if (!north.count(key)) continue;

        sort(E.begin(), E.end());

        for (int N_x : north[key]) {
            auto left = lower_bound(E.begin(), E.end(), N_x - K + 1);
            auto right = upper_bound(E.begin(), E.end(), N_x);

            answer -= right - left;
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
