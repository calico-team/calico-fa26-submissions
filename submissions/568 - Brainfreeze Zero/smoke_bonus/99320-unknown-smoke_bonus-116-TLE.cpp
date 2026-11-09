#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back

int solve(){
    int n, r;
    cin >> n >> r;
    vector<int> a;
    for(int i=0; i<n; i++){
        int g;
        cin >> g;
        a.pb(g);
    }
    bool first_smoke = true;
    int first_smoke_time = 0;
    bool second_smoke = true;
    int second_smoke_time = 0;
    bool x =true;
    for(int i=0; i<n; i++){
        if(!first_smoke && first_smoke_time <= a[i]){
            first_smoke = true;
        }
        if(!second_smoke && second_smoke_time <= a[i]){
            second_smoke = true;
        }
        if(first_smoke){
            first_smoke = false;
            first_smoke_time = a[i]+r;
        }
        else if(!first_smoke && second_smoke){
            second_smoke = false;
            second_smoke_time = first_smoke_time+r;
        }
        else{
            cout << "NO" << endl;
            x = false;
            break;
        }
        
    }
    if(x){
        cout << "YES" << endl;
    }
    return 0;
}

int32_t main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;

}