#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define int long long

/*
n - sum(cnt(x,y)+1)

where cntz is number of drones at (x,y)

consider this drone to be moving right

we will never intersect any drone moving right
let right moving start at (a,b) up moving start at (c,d)
a + t = c
b + t = d
a + b = c + d


so we just require that t < k for each  

each drone can only intersect one other drone each night
*/
int32_t main(){

    int tt; cin >> tt;

    while(tt--){
        int n, k; cin >> n >> k;

        //only intersect when sum of coords is the same;
        map<int, vector<int>> r;
        map<int, vector<int>> u;
    

        for(int i = 1; i <= n; i++){
            int x,y,z; cin >> x >> y >> z;

            char di; cin >> di;

            if(di == 'E') r[x+y].push_back(x);
            else u[x+y].push_back(x);
        }


        int ans = n * k;

        for(auto [a,v] : r){

            vector<int> up = u[a];

            sort(up.begin(), up.end());
            for(int x : v){
                //count number of x values of u such that a < x < a + k

                auto lo = upper_bound(up.begin(), up.end(), x);
                auto hi = lower_bound(up.begin(), up.end(), x + k);                
                ans -= hi - lo;
            }   
        }

        cout << ans << "\n";




    }
}