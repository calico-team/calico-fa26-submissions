#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//void solve(){


//}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;

    while(t--){
        ll N, R; cin >> N >> R;
        
        vector<ll> timestamps(N);

        for(auto& x : timestamps){
            cin >> x;
        }

        if(N <= 2){
            cout << "Yes" << "\n";
            continue;
        }

        int charge_count = 1;
        bool can_do = true;


        for(int i = 1; i < N ; i++){
            ll gap =  timestamps[i] - timestamps[i-1];
           
            if(charge_count == 0){
                can_do = false;
                break;
            }else if(gap >= R && charge_count < 2){
                charge_count++;
            }else{
                charge_count--;
                if (charge_count < 0){ charge_count = 0;}
            }

            
        }


        if(can_do){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }

    }

}