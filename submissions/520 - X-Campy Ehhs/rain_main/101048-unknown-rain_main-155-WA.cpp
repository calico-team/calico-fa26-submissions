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
    
    for (int qqqq = 0; qqqq < K; qqqq++) {
        vector<bool> LL(N,false);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (get<0>(L[i]) == get<0>(L[j]) and get<1>(L[i]) == get<1>(L[j])) {
                    if (get<2>(L[i]) > get<2>(L[j])) {
                        LL[i] = false;
                    } else {
                        LL[i] = true;
                    }
                } else {
                    LL[i] = true;
                }
            }
        }
        for (auto i : LL) {
            if (i) {
                answer += 1;
            }
        }
        for (int i = 0; i < N; i++) {
            if (get<3>(L[i]) == 'E') {
                get<0>(L[i]) += 1;
            } else {
                get<1>(L[i]) -= 1;
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
