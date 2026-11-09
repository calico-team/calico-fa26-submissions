#include <iostream>
#include <tuple>
#include <set>
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
    long long answer = 0;

    for (int night = 1; night <= K; night ++) {
        set<pair<int, int>> taken;
        for (int drone = 0; drone < N; drone ++) {
            if (taken.find(make_pair(get<0>(L[drone]), get<1>(L[drone]))) == taken.end()) {
                answer ++;
                taken.insert(make_pair(get<0>(L[drone]), get<1>(L[drone])));
            }
        }

        for (int drone = 0; drone < N; drone ++) {
            if (get<3>(L[drone]) == 'N') {
                get<1>(L[drone]) ++;
            } else if (get<3>(L[drone]) == 'E') {
                get<0>(L[drone]) ++;
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
