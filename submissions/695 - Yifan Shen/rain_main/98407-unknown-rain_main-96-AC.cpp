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

    vector<pair<long long, long long>> NO;

    for (int i = 0; i < N; i++) {

        if (get<3> (L[i]) == 'N') {

            NO.push_back({(long long) get<0> (L[i]) + get<1> (L[i]), (long long) get<0> (L[i])});

        }

    }

    sort(NO.begin(), NO.end());

    for (int i = 0; i < N; i++) {

        int xi = get<0> (L[i]);
        int yi = get<1>(L[i]);
        char di = get<3> (L[i]);

        if (di == 'N') {

            continue;

        }

        over += upper_bound(NO.begin(), NO.end(), pair<long long, long long> (xi + yi, xi + K - 1)) - lower_bound(NO.begin(), NO.end(), pair<long long, long long> (xi + yi, xi));

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
