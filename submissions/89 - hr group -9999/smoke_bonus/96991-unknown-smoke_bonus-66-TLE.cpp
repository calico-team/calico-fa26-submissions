#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n, r;
    cin >> n >> r;
    vector<int> arr;
    // state = time     cur             charge
    vector<pair<int, pair<int, int>>> states;
    states.clear();
    states.push_back({0, {2, 0}});

    //cout << n << " " << r << endl;
    bool good = true;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        arr.push_back(a);
        pair<int, pair<int, int>> prev = states[states.size() - 1];
        if(prev.second.first == 2){
            // just use
            states.push_back({a, {1, 0}});
        } else if(prev.second.first == 1){
            // one + charge

            if(a - prev.first + prev.second.second >= r){
                // two filled
                states.push_back({a, {1, 0}});
            } else{
                states.push_back({a, {0, a - prev.first + prev.second.second}});
            }
        } else{
            //zero + charge

            if(a - prev.first + prev.second.second >= 2 * r){
                // both recharged
                states.push_back({a, {1, 0}});
            } else if(a - prev.first + prev.second.second >= r){
                // only charged one
                states.push_back({a, {0, prev.second.second + a - prev.first           - r}});
            } else{
                good = false;
            }
        }
    }
    if(!good){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    return;
}
signed main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}