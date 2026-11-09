#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
using namespace std;
using ll = long long;
const int INF = 1e9;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt; cin >> tt;
    while(tt--){
        int n, k; cin >> n >> k;
        vector<pair<int,int>> drone_locations(n);
        vector<pair<int,int>> drone_movement(n);
        for(int i = 0; i < n; ++i){
            int x,y,z; cin >> x >> y >> z;
            drone_locations[i].first = x; drone_locations[i].second = y;
            char c; cin >> c;
            if(c == 'N'){drone_movement[i].first = 0; drone_movement[i].second = 1;}
            if(c == 'S'){drone_movement[i].first = 0; drone_movement[i].second = -1;}
            if(c == 'E'){drone_movement[i].first = 1; drone_movement[i].second = 0;}
            if(c == 'W'){drone_movement[i].first = -1; drone_movement[i].second = 0;}
        }
        ll total = k*n;
        //find intersections
        vector<vector<bool>> intersections(n,vector<bool>(n));
        ll minus = 0;
        for(int  i = 0; i < n-1; ++i){
            auto [x1,y1] = drone_locations[i];
            for(int j = i+1; j < n; j++){
                auto[x2,y2] = drone_locations[j];
                // one going right and one going up | one going right and one going down | one going left and one going up | one going left and one going down
                int dx1 = drone_movement[i].first, dx2 = drone_movement[j].first, dy1 = drone_movement[i].second, dy2 = drone_movement[j].second;
                if(dy1 == 0 && dx2 == 0){ 
                    int time = dx1* (x2-x1);
                    if (time >= 0 && time < k && time == (y1-y2)*dy2 && !intersections[i][j]){minus++; intersections[i][j]=true;}
                }
                if(dx1 == 0 && dy2 == 0){ 
                    int time = dy1* (y2-y1);
                    if (time >= 0 && time < k && time == (x1-x2)*dx2 && !intersections[i][j]){minus++; intersections[i][j]=true;}
                }
            }
        }
        cout << total - minus << "\n";
    }
    
    return 0;
}