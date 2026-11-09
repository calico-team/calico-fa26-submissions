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
struct T {
    int x;
    int y;
    int z;
    char d;
    bool operator < (const T& o) {
        if (x == o.x) {
            if (o.d == 'N') return false;
        }
        return x < o.x;
    }
};
long long solve(int N, int K, vector<T>& L){
    long long ans = N;
    ans *= K;
    long long answer = 0;
    unordered_map<int, vector<int>> m;
    for (int i = 0; i < L.size(); i++) {
        m[L[i].x + L[i].y].push_back(i);
    }
    sort(L.begin(), L.end());
    for (auto& p : m) {
        vector<int>& v = p.second;
        vector<T> after;
        for (int i = 0; i < v.size(); i++) {
            after.push_back(L[v[i]]);
        }
        map<pair<int, int>, int> originalPos;
        for (int i = 0; i < after.size(); i++) {
            originalPos[make_pair(after[i].x, after[i].y)] = i;
        }
        for (int i = 0; i < after.size(); i++) {
             if (after[i].d == 'N') {
                after[i].y += K;
            } else {
                after[i].x += K;
            }
        }
        sort(after.begin(), after.end());
        for (int i = 0; i < after.size(); i++) {
            if (after[i].d == 'E') {
                ans -= i - originalPos[make_pair(after[i].x - K, after[i].y)];
            }
        }
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<T> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}
