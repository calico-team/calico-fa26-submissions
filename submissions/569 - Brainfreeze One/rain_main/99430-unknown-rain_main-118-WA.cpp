#include <bits/stdc++.h>
using namespace std;
 

void solve(){
    int n, k; // n = drones, k = nights
    cin >> n >> k;
    vector<vector<int>> north_drones;
    vector<vector<int>> east_drones;
    vector<string> drones_direction;

    for (int i=0; i<n; i++) {
        int x, y, z;
        string d;
        cin >> x >> y >> z >> d;
        vector<int> cords;
        cords.push_back(x);
        cords.push_back(y);

        if (d == "N") {
            north_drones.push_back(cords);
        } else {
            east_drones.push_back(cords);
        }
    }

    long long rainWater = n * k; 
    for (int i = 0; i < north_drones.size(); i++) {
        for (int j = 0; j < east_drones.size(); j++) {
            int dx = north_drones[i][0] - east_drones[j][0];
            int dy = north_drones[i][1] - east_drones[j][1];
            
            // cout << dx << " " << dy << "\n";
            if (dx == -dy && dx > 0 && dy < 0 && abs(dx) < k) {
                rainWater--;
            }
        }
    }

    cout << rainWater << "\n";
}
int main()
{
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}