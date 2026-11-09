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
	for (int i = 0; i < K; i++) {
		sort(L.begin(), L.end());
		int subtractor = 0;
		for (size_t j = 0; j<L.size(); j++) {
			if (j != L.size() - 1 && get<0>(L[j]) == get<0>(L[j+1])) {
				if (get<1>(L[j]) == get<1>(L[j+1])) subtractor++;
			}
		}
		for (auto& item : L) {
			switch(get<3>(item)) {
				case 'N':
					get<1>(item)++;
					break;
				case 'S':
					get<1>(item)--;
					break;
				case 'E':
					get<0>(item)++;
					break;
				case 'W':
					get<0>(item)--;
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
