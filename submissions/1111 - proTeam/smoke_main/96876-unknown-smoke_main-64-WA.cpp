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
            int gap =  timestamps[i] - timestamps[i-1];
           
            //refill
            int possible_recharge = gap / R;
            charge_count = (ll)min(charge_count+ possible_recharge, 2);

            //use charge
            charge_count--;
            
            if(charge_count < 0){
                can_do = false;
                break;
            }


            
        }


        if(can_do){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }

    }

}