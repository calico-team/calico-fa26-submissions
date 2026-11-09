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

long long solve(int N, int K, vector<int> Ex, vector<int> Ey, vector<int> Nx, vector<int> Ny){
    long long answer = 1LL * N * K;

    for (int i = 0; i < (int)Nx.size(); i++) {
        for (int j = 0; j < (int)Ex.size(); j++) {
            long long t = (long long)Nx[i] - Ex[j];
            if (t == (long long)Ey[j] - Ny[i] && 0 <= t && t < K) {
                answer--;
            }
        }
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<long long> Ey, Ny, Ex, Nx;
        for (long long i = 0; i < N; i++){
            long long X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            if(D == 'E'){
                Ex.push_back(X);
                Ey.push_back(Y);
            } else{
                Nx.push_back(X);
                Ny.push_back(Y);
            }
        }
        cout<<solve(N, K, Ex, Ey, Nx, Ny)<<endl;
    }
}
