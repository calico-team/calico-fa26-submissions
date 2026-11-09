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

long long solve(int N, int K, vector<tuple<int, int, int, char>>& L){
    long long answer =0;
	for (int i = 0; i < K; i++) {
		int subtractor = 0;
		unordered_set<string> seen;
		
		for (auto& item : L) {
			int& ix = get<0>(item);
			int& iy = get<1>(item);
			
			string pos = to_string(ix) + ":" + to_string(iy);
			
			if (seen.find(pos) != seen.end()) subtractor++;
			else seen.insert(pos);
			
			switch(get<3>(item)) {
				case 'N':
					iy++;
					break;
				case 'S':
					iy--;
					break;
				case 'E':
					ix++;
					break;
				case 'W':
					ix--;
					break;
			}
		}
		answer += N - subtractor;
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
