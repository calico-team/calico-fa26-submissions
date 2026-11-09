//
// Created by User on 11/8/2026.
//

#include "bits/stdc++.h"
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin>>cases;
    while (cases>0) {
        cases--;
        unordered_map<int,vector<pair<int,int>>> east;
        vector<pair<int,int>> north;
        int drones, nights;
        cin>>drones>>nights;

        for (int i=0; i<drones; i++) {
            int x,y,z;
            char dir;
            cin>>x>>y>>z>>dir;
            if (dir=='E') {
                east[x+y].emplace_back(x,y);
            }else {
                north.emplace_back(x,y);
            }
        }
        int anti=0;
        for (int i=0; i<north.size(); i++) {
            auto& [nx,ny]=north[i];
            for (int j=0; j<east[nx+ny].size(); j++) {
                auto& [bx,by]=east[nx+ny][j];
                if (abs(nx-bx)<=nights) {
                    anti++;
                }
            }
        }
        long long count=nights*drones-anti;
        cout<<count<<"\n";
    }

}