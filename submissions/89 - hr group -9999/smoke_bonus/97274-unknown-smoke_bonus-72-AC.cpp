#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n, r;
    cin >> n >> r;
    vector<int> arr;
    // state = time     cur             charge
    pair<int, pair<int, int>> prev = {0, {2, 0}};

    //cout << n << " " << r << endl;
    bool good = true;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        arr.push_back(a);
        if(prev.second.first == 2){
            // just use
            prev = {a, {1, 0}};
        } else if(prev.second.first == 1){
            // one + charge

            if(a - prev.first + prev.second.second >= r){
                // two filled
                prev = {a, {1, 0}};
            } else{
                prev = {a, {0, a - prev.first + prev.second.second}};
            }
        } else{
            //zero + charge

            if(a - prev.first + prev.second.second >= 2 * r){
                // both recharged
                prev = {a, {1, 0}};
            } else if(a - prev.first + prev.second.second >= r){
                // only charged one
                prev = {a, {0, prev.second.second + a - prev.first           - r}};
            } else{
                good = false;
            }
        }
    }
    if(!good){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    return;
}
signed main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}