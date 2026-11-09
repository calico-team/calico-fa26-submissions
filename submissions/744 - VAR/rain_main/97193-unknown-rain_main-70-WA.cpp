#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <array>

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

long long solve(int n, int k, vector<tuple<int, int, int, char>> l){

    map<int, vector<int>> north,east;
    for (int i=0; i<n; i++) {
        int x=get<0>(l[i]); int y=get<1>(l[i]);
        if (get<3>(l[i])=='E') {
            if (east.find(x+y)==east.end()) {east[x+y]=vector<int>();}
            east[x+y].push_back(x);
        }else {
            if (north.find(x+y)==north.end()) {north[x+y]=vector<int>();}
            north[x+y].push_back(x);
        }
    }
    int intersects=0;
    for (auto &[sum,a] : east) {
        if (north.find(sum)==north.end()) continue;

        auto b = north[sum];
        sort(b.begin(), b.end());
        for (int x : a) {

            int lo=upper_bound(b.begin(), b.end(), x) - b.begin();
            int hi=lower_bound(b.begin(), b.end(), x+k) - b.begin() - 1;

            if (lo==b.size() || hi==-1 || hi<lo) continue;
            intersects += (hi-lo+1);
        }

    }
    long long ans = n*k - intersects;

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
