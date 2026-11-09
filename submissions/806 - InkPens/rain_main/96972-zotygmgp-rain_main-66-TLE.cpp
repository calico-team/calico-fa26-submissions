// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t; 
    for (int x = 0; x <t; x++){
        int N,K; cin >> N >> K;
        int total = 0; 
        vector<vector<int>> drones_pos;
        vector<char> directions;
        for (int i = 0; i < N; i++){
            int X, Y, Z;  char Direction; cin >> X >> Y >> Z >> Direction; 
            drones_pos.push_back({X, Y, Z});
            directions.push_back(Direction);
        }

        for (int g = 0; g < K; g++){ //for each night 
            //for each drone 
            for (int i = 0; i < N; i ++){
                bool covered = false; 

                 for (int j = 0; j < N; j++) {
                    if (i == j) continue; //if ur comparing a drone to iself 
                    //X =0 Y = 1 Z = 2
                    //cover checker 
                    if(drones_pos[i][0] == drones_pos[j][0]&& //if xs equal
                      drones_pos[i][1] == drones_pos[j][1]&& //if ys equal
                      drones_pos[j][2] > drones_pos[i][2]){
                        covered = true;
                        break;
                      }  
                 }
                 if(!covered){ //if not covered, collect a droplet yay
                        total += 1; //droplet collected!!
                  }
            }
             for (int i = 0; i < N; i++) {
                    if(directions[i] == 'E'){
                        drones_pos[i][0] += 1;
                            //i0 is the x value 
                    }
                    else{
                        drones_pos[i][1] += 1;
                            //i1 is the y value 
                  }
               }
        }
        cout << total << "\n";

    }

}
