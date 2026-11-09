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
class Drone {
    public: int X, Y, Z;
    public: char D;

    public: Drone(int X, int Y, int Z, char D) {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
        this->D = D;
    }
};

static long intersect(Drone d1, Drone d2, int K){
    if(d1.D == d2.D){
        return 0;
    }
    
    const Drone& r = (d1.D == 'E') ? d1 : d2;
    const Drone& u = (d1.D == 'E') ? d2 : d1;

    if(r.Y - u.Y == u.X - r.X && r.Y - u.Y < K && r.Y - u.Y > 0){
        // System.out.println(r);
        // System.out.println(u);
        // System.out.println(r.Y - u.Y);
        return 1;
    }
    return 0;
}

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    vector<Drone> drones;
    drones.reserve(N);
    for (auto& [x, y, z, d] : L){
        drones.emplace_back(x, y, z, d);
    }

    long long total = (long long) N * K;

    if(N == 1){
        return K;
    }

    for(int i = 0; i < N-1; i++){
        for(int j = i+1; j < N; j++){
            total -= intersect(drones[i],drones[j],K);
        }
    }

    return total;
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
