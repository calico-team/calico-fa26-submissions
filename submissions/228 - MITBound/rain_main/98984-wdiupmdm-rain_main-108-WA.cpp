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
    vector<pair<int,int>> Evec;
    vector<pair<int,int>> Nvec;
    long long n = 0;
    for(int i = 0; i < N; i++)
    {
        if(get<3>(L[i]) == 'E')
        {
            Evec.push_back({get<0>(L[i]),get<1>(L[i])});
        } else {
            Nvec.push_back({get<0>(L[i]),get<1>(L[i])});
        }
    }

    for(int i = 0; i < Evec.size(); i++)
    {
        for(int j = 0; j < Nvec.size(); j++)
        {
            int k = Evec[i].second - Nvec[j].second;
            if(Nvec[j].first - Evec[i].first == k && k <= (K-1))
            {
                n++;
            }
        }
    }
    answer = N*K - n;
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
