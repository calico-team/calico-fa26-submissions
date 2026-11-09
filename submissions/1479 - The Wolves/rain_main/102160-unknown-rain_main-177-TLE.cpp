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
long long answer = 0;

vector<int> X(N);
vector<int> Y(N);
vector<int> Z(N);
vector<char> D(N);

for (int i = 0; i < N; i++){
X[i] = get<0>(L[i]);
Y[i] = get<1>(L[i]);
Z[i] = get<2>(L[i]);
D[i] = get<3>(L[i]);
}
for (int night = 0; night < K; night++){

for (int j = 0; j < N; j++){
        bool blocked = false;
    for (int i = 0; i < N; i++){
if (X[i] == X[j] && Y[i] == Y[j]){
        if(Z[i]>Z[j]){
        blocked = true;
break;
        }
}
}
if (!blocked){
answer++;
}
}
for(int index=0; index<N; index++){
    if(D[index] == 'E') {
        X[index]++;
    }
    if(D[index]=='N') {
    Y[index]++;
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
