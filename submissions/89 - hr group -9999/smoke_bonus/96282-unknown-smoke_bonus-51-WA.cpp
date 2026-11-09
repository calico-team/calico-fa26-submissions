#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n, r;
    cin >> n >> r;
    vector<int> arr;
    // state = time     cur             charge
    vector<pair<int, pair<int, int>>> states;
    states.clear();
    states.push_back({0, {2, 0}});

    //cout << n << " " << r << endl;

    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        arr.push_back(a);
        pair<int, pair<int, int>> prev = states[states.size() - 1];
        if(prev.second.first == 2){
            // just use
            states.push_back({a, {1, 0}});
        } else if(states[states.size() - 1].second.first == 1){
            // one + charge

            if(a - prev.first + prev.second.second >= r){
                // two filled
                states.push_back({a, {1, 0}});
            } else{
                states.push_back({a, {0, prev.second.second}});
            }
        } else{
            //zero + charge
            
            if(a - prev.first + prev.second.second >= 2 * r){
                // both recharged
                states.push_back({a, {1, 0}});
            } else if(a - prev.first + prev.second.second >= r){
                // only charged one
                states.push_back({a, {0, prev.second.second}});
            } else{
                string trash;
                getline(cin, trash);
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
    return;
    /*
    int cur = 2;
    int charge = 0;
    int ind = 0;
    //cout << "here" << endl;
    for(int t = 0; t <= 1e5, ind < n; t++){
        // charge first
        if(cur < 2){
            charge++;
            if(charge == r){
                cur++;
                charge = 0;
            }
        }
        if(t == arr[ind]){
            cur--;
            if(cur == -1){
                cout << "NO" << endl;
                return;
            }
            ind++;
        }
    }
    cout << "YES" << endl;
    */
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}