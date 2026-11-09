#include<bits/stdc++.h>
using namespace std;

#define bismillah ios::sync_with_stdio(0); cin.tie(0);
#define alhamdulillah return 0;

using ll = long long;

int main(){
    bismillah

    int tt; cin >> tt;
    while(tt--){
        int n;
        ll r; cin >>n >> r;


        ll tm_1 = 0, tm_2 = 0;
        ll cur_tm = 0;

        vector<ll> a_n(n);
        for(auto &x : a_n) cin >> x;

        bool flag = 1;

        for(int i = 0; i<n; i++){
            // bool flag = 0;
            ll a = a_n[i];
            cur_tm = a;
            if((cur_tm-tm_1) >= r || tm_1 == 0){
                // flag = 1;
                tm_1 = cur_tm;
                // cout << "OK" << "\n";
                continue;
            }
            if((cur_tm-tm_2) >= r || tm_2 == 0){
                tm_1 = cur_tm;
                tm_2 = cur_tm+r;
                // cout << "OK" << "\n";
                continue;
            }
            flag = 0;
            break;
        }

        if(flag){
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }

    alhamdulillah
}