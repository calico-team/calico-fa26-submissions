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
struct T1 {
    int x;
    int y;
    int z;
    char d;
    bool operator < (const T1& o) {
        if (x == o.x) {
            if (o.d == 'E') return false;
        }
        return x < o.x;
    }
};
struct T2 {
    int x;
    int y;
    int z;
    char d;
    bool operator < (const T2& o) {
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
    for (auto& p : m) {
        vector<int>& v = p.second;
        vector<T1> after1;
        for (int i = 0; i < v.size(); i++) {
            after1.push_back({L[v[i]].x, L[v[i]].y, L[v[i]].z, L[v[i]].d});
        }
        map<pair<int, int>, int> originalPos;
        for (int i = 0; i < after1.size(); i++) {
            originalPos[make_pair(after1[i].x, after1[i].y)] = i;
        }
        vector<T2> after2;
        for (int i = 0; i < after1.size(); i++) {
             if (after1[i].d == 'N') {
                after2.push_back({after1[i].x, after1[i].y + K, after1[i].z, after1[i].d});
            } else {
                after2.push_back({after1[i].x + K, after1[i].y, after1[i].z, after1[i].d});
            }
        }
        sort(after2.begin(), after2.end());
        for (int i = 0; i < after2.size(); i++) {
            if (after2[i].d == 'E') {
                ans -= i - originalPos[make_pair(after2[i].x - K, after2[i].y)];
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
