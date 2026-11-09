#include <bits/stdc++.h>
#include<vector>
#include<map>
#include<algorithm>
#define ll long long
#define all(x) x.begin(),x.end()
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
    long long ans = N;
    ans*=K;
    map<int,vector<int>>ps;
    vector<pair<int,int>>v;
    for(auto[x,y,z,c]:L){
        if(c=='N'){
            ps[y+x].push_back(y);
        }else{
            v.push_back({x,y});
        }
    }
    for(auto&[a,b]:ps)sort(all(b));
    for(auto[x,y]:v){
        auto&arr = ps[y+x];
        int a = (upper_bound(all(arr),y)-arr.begin())-(upper_bound(all(arr),(y-K))-arr.begin());
        //cout<<a<<' ';
        ans -= a;
    }
    return ans;
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
