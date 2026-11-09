#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n, r;
    cin >> n >> r;
    vector<int> arr;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        arr.push_back(a);
    }
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
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}