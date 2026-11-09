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
    map<int, vector<tuple<int, int, char>>> groups;
    for (auto& [x, y, z, d] : L) {
        groups[x + y].push_back({x, z, d});
    }

    long long blocked_times = 0;

    for (auto& [sum_xy, robots] : groups) {
        sort(robots.begin(), robots.end());

        multiset<int> active_z;
        queue<pair<int, int>> window; 

        for (auto& robot : robots) {
            int x = get<0>(robot);
            int z = get<1>(robot);
            char d = get<2>(robot);

            while (!window.empty() && window.front().first <= x - K) {
                active_z.erase(active_z.find(window.front().second));
                window.pop();
            }
            if (d == 'N') {
                int below = distance(active_z.begin(), active_z.lower_bound(z));
                int above = distance(active_z.upper_bound(z), active_z.end());
                blocked_times += (below + above);
            } else {
                active_z.insert(z);
                window.push({x, z});
            }
        }
    }
    return (long long)N * K - blocked_times;
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
