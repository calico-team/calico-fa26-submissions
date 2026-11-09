#include <tuple>
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
    for(int n=0; n<K; n++){
    	for(int i=0; i<N; i++){
    		bool b=false;
    		int x=get<0>(L[i]);
			int y=get<1>(L[i]); 
			int z=get<2>(L[i]);
			char D=get<3>(L[i]); 
			for(int j=0; j<N;j++){
				if (i == j)
                    continue;

                int x2 = get<0>(L[j]);
                int y2 = get<1>(L[j]);
                int z2 = get<2>(L[j]);

                if (x == x2 && y == y2 && z < z2) {
                    b = true;
                    break;
                }
			}
			if (!b) {
                answer++;
            }
		}
		for (int i = 0; i < N; i++) {

            if (get<3>(L[i]) == 'E') {
                get<0>(L[i])++;
            }
            else if (get<3>(L[i]) == 'N') {
                get<1>(L[i])++;
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

