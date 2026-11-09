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

long long solve(int N, int K, const vector<tuple<int, int, int, char>>& L) {
    unordered_map<int,vector<int>> e, n; // e[x+y] = {y values}
    for (const auto& [x,y,z,l] : L) {
        if (l == 'N') n[x+y].push_back(y);
        else e[x+y].push_back(y);
    }
    long long collisions = 0;
    for (auto& [a,b] : n) { // collisions from ts x+y value is number of pairs of e.y-n.y between 0 and K
        if (e.count(a)) {
            sort(e[a].begin(),e[a].end());
            for (int i : b) {
                collisions += lower_bound(e[a].begin(),e[a].end(),i+K)-upper_bound(e[a].begin(),e[a].end(),i);
                // for (int j : e[a]) {
                //     if (j-i > 0 && j-i < K) collisions++; // can't have the same x+y and y values, otherwise same spot
                // }
            }
        }
    }
    return (long long)N*K-collisions;
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
