#include <bits/stdc++.h>
using namespace std;
 

void solve(){
    long n, k; // n = drones, k = nights
    cin >> n >> k;
    vector<vector<long>> north_drones;
    vector<vector<long>> east_drones;

    for (int i=0; i<n; i++) {
        long x, y, z;
        string d;
        cin >> x >> y >> z >> d;
        vector<long> cords;
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
            long dx = north_drones[i][0] - east_drones[j][0];
            long dy = north_drones[i][1] - east_drones[j][1];

            
            // cout << dx << " " << dy << "\n";
            if (dx == -dy && dx > 0 && abs(dx) < k) {
                // cout << "i: " << i << " coords: (" << north_drones[i][0] << ", " << north_drones[i][1] << ")";
                // cout << " j: " << j << " coords: (" << east_drones[j][0] << ", " << east_drones[j][1] << ")" << "\n";

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