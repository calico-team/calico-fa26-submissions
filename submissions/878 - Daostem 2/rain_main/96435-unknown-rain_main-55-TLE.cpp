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
    for(int a = 1; a<=K; a++){
    	//check distinctness 
    	  set<tuple<int, int>> distinctxypair; 

    	for(int j = 1; j<=N; j++){
    		tuple<int, int, int, char> temp = L[j-1];

    	auto temp1= make_tuple(get<0>(temp), get<1>(temp));
			distinctxypair.insert(temp1);
    	}
    	answer+=distinctxypair.size();
    //	cout<<"Night "<<a+1<< ": "<<answer<<endl;
    	distinctxypair.clear();
    	//now move everything! 
    	for(int i = 1; i<=N; i++){
    		   tuple<int, int, int, char> temp = L[i-1];
    		  // 	cout<<get<0>(temp)<<" "<<get<1>(temp)<<" "<<get<2>(temp);
  
			   char c = get<3>(temp); // N or E
			//   cout<<" "<<c<<endl;
			   if(c=='E'){
			   	int u=get<0>(temp);
			   	get<0>(temp)=u+1;
			   }
			   else{
			   	int u=get<1>(temp);
			   	get<1>(temp)=u+1;
			   }
			  L[i-1]=temp;
			//  	cout<<get<0>(temp)<<" "<<get<1>(temp)<<" "<<get<2>(temp)<<endl;

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