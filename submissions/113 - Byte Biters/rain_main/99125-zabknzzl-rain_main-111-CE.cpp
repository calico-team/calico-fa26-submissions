#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--){
       int n, k; cin >> n >> k;
       map<int,vector<int>> ed,nd;
       for(int i = 0; i < n; ++i){
            int x,y,z; cin >> x >> y >> z;
            char c; cin >>c;
            if(c=='E'){
                ed[x+y].push_back(x);
            } else{
                nd[x+y].push_back(x);
            }
        }
        ll total = 1LL * k * n;
        ll minus = 0;
        for(auto& [sum,ex]:ed){
            if(!nd.count(sum))continue;
            auto north_xs = nd[sum];
            sort(north_xs.begin(),north_xs.end());
            for(int x : ex){
                ll far = (ll)x + k -1;
                if(far > 100000){
                    far = 100000;
                }
                auto L = lower_bound(north_xs.begin(),north_xs.end(), x);
                auto R = upper_bound(north_xs.begin(),north_xs.end(), (int)far);
                minus += R-L;
            }
        }
        cout << total - minus << endl;
    }
    return 0;
}