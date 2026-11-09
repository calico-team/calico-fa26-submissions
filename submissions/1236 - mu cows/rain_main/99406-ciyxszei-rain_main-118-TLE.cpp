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
    long long answer =0;
    set<pair<int, int>> rained;
    for (int nights = 0; nights < K; nights++) {
        for (int i = 0; i < L.size(); i++) {
            pair<int, int> coords = {get<0>(L[i]), get<1>(L[i])};
            char direction = get<3>(L[i]);
            if (rained.find(coords) == rained.end()) {
                rained.insert(coords);
                answer++;
            }
            if (direction == 'E') {
                get<0>(L[i])++;
            } else {
                get<1>(L[i])++;
            }
        }
        rained.clear();
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
