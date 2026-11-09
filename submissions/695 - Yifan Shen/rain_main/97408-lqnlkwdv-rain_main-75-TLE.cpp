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
    long long answer = (long long) N * K;
    long long over = 0;

    for (int i = 0; i < N; i++) {

        int xi = get<0> (L[i]);
        int yi = get<1>(L[i]);
        char di = get<3> (L[i]);

        if (di == 'N') {

            continue;

        }

        for (int j = 0; j < N; j++) {

            int xj = get<0> (L[j]);
            int yj = get<1> (L[j]);
            char dj = get<3> (L[j]);

            if (dj == 'N') {

                if (xj - xi == yi - yj) {

                    if (xj - xi < K && xj - xi >= 0) {

                        over ++;

                    }

                }

            }

        }

    }

    return answer - over;
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
