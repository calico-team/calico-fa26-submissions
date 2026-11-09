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

int overlaps(vector<int> v1, vector<int> v2, int lower) {
    int count = 0;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    int left = 0;
    int right = v2.size() - 1;
    while (left < v1.size() && right >= 0) {
        if (v1[left] + v2[right] >= lower) {
            count += v1.size() - left;
            right--;
        }
        left++;
    }
    return count;
}

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    long long answer = N * K;
    unordered_map<int, vector<int>> norths;
    unordered_map<int, vector<int>> easts;
    for (tuple<int, int, int, char> drone : L) {
        int xcoord = get<0>(drone);
        int ycoord = get<1>(drone);
        char dir = get<3>(drone);
        if (dir == 'N') {
            norths[xcoord + ycoord].push_back(ycoord);
        } else {
            easts[xcoord + ycoord].push_back(xcoord);
        }
    }

    for (const auto&[key, value] : norths) {
        if (easts.find(key) != easts.end()) {
            answer -= overlaps(value, easts[key], key - K + 1);
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
