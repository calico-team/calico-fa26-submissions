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

struct drone{
	int x,y,z;
	char d;
};

long long solve(int N, int K, vector<drone> L){
    long long answer = N*K;
    long long blocked = 0;
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(L[i].d=='E'&&L[j].d=='N'){
				if(L[j].x-L[i].x==L[i].y-L[j].y){
					long long diff = L[j].x-L[i].x;;
					if(diff<K&&diff>0){
						blocked++;
//						cout<<"block with drones "<<i+1<<" and "<<j+1<<", diff at "<<diff+1<<endl;
					}
				}
			}
			if(L[i].d=='N'&&L[j].d=='E'){
				if(L[i].x-L[j].x==L[j].y-L[i].y){
					long long diff = L[i].x-L[j].x;;
					if(diff<K&&diff>0){
						blocked++;
//						cout<<"block with drones "<<i+1<<" and "<<j+1<<", diff at "<<diff+1<<endl;
					}
				}
			}
			
		}
	}
    return answer-blocked;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<drone> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X,Y,Z,D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}

