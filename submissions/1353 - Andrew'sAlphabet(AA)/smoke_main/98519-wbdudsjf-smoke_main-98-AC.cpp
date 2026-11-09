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
        int n, r; cin >> n >> r;
        vector<int> arr(n);
        for(int i = 0 ; i < n; ++i)cin >> arr[i];
        ll smoke_count = 2, smoke_recharge1 = -1, smoke_recharge2 = -1;
        bool passed = true;
        for(int i = 0; i < n && passed; ++i){
            ll cur_time = arr[i];
            if(smoke_recharge1 <= cur_time && smoke_recharge1 != -1){
                smoke_count++;
                smoke_recharge1 = -1;
            }
            if(smoke_recharge2 <= cur_time && smoke_recharge2 != -1){
                smoke_count++;
                smoke_recharge2 = -1;
            }
            if(smoke_count == 2){
                if(smoke_recharge1 == -1){
                    smoke_count--;
                    smoke_recharge1 = r+cur_time;
                }
                else if (smoke_recharge2 == -1){
                    smoke_count--;
                    smoke_recharge2 = r+cur_time;
                }
            }
            else if(smoke_count == 1){
                if(smoke_recharge1 == -1){
                    smoke_count--;
                    smoke_recharge1 = smoke_recharge2+r;
                    
                }
                else if(smoke_recharge2 == -1){
                    smoke_count--;
                    smoke_recharge2 = smoke_recharge1+r;
                }
            }
            else{
                passed =false;
            }
        }
        cout << (passed ? "YES" : "NO") << "\n";
    }
    return 0;
}