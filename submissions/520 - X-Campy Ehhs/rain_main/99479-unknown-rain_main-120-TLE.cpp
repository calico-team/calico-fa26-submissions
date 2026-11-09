#include <iostream>
#include <vector>
#include <set>
using namespace std;

long long countUniqueXYPairs(vector<tuple<int, int, int, char>>& L) {
    set<pair<int, int>> seen;
    for (auto[x, y, z, d] : L) {
        seen.insert({x, y});
    }
    long long ans = seen.size();
    return ans;
}

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

long long solve(int N, int K, vector<tuple<int, int, int, char>>& L){
    long long answer = countUniqueXYPairs(L);
    K--;
    while (K--) {
        for (int i = 0; i < N; i++) {
            char D = get<3>(L[i]);
            if (D == 'E') {
                get<0>(L[i]) += 1;
            }
            else if (D == 'N') {
                get<1>(L[i]) += 1;
            }
        }

        answer += countUniqueXYPairs(L);
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
