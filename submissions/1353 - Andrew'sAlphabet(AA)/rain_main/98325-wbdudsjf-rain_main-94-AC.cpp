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
       map<int,vector<int>> east_drones,north_drones;
       for(int i = 0; i < n; ++i){
            int x,y,z; cin >> x >> y >> z;
            char c; cin >>c;
            if(c=='E') east_drones[x+y].push_back(x);
            else north_drones[x+y].push_back(x);
        }
        ll total = 1LL * k * n;
        ll minus = 0;
        for(auto& [sum,east_xs]:east_drones){
            if(!north_drones.count(sum))continue;
            auto north_xs = north_drones[sum];
            sort(north_xs.begin(),north_xs.end());
            for(int x : east_xs){
                ll far = (ll)x + k -1;
                if(far > 100000)far = 100000;
                auto L = lower_bound(north_xs.begin(),north_xs.end(), x);
                auto R = upper_bound(north_xs.begin(),north_xs.end(), (int)far);
                minus += R-L;
            }
        }
        cout << total - minus << "\n";
    }
    return 0;
}