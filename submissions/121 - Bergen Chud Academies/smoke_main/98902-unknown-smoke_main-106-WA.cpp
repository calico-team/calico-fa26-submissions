#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, r;
    cin >> n >> r;

    int charges = 2;
    bool cont = true;
    int last = -4e18;

    for (int i = 0; i < n; i ++){
        int time;
        cin >> time;

        if (last <= time && charges < 2){
            //refill
            charges ++;
            if (charges < 2){
                last += r;
            }
        }
        
        if (charges == 0){
            cont = false;
        }
        else{
            charges --;
            last = time + r;
        }

    }

    if (cont){
        cout << "YES" << "\n";
    }
    else{
        cout << "NO" << "\n";
    }
}

int32_t main(){
    int tt;
    cin >> tt;
    while(tt--){
        solve();
    }
}