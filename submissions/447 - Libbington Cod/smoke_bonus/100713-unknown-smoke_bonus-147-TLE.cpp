#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define ll long long
int main() {
    ll matches; 
    cin >> matches; 

    for (int m = 0; m < matches; m++) {
        ll pings, regen;
        cin >> pings >> regen; 

        vector<ll> calls(1000000);
        for (ll i = 0; i < pings; i++) {
            cin >> calls[i];
        }
        
         ll smokes = 2;
         ll cd = 0; 
         ll comm = 0;
         bool clutch = true; 

         ll last_comm = calls[pings - 1];

         for (ll timer = 1; timer <= last_comm; timer++){

            if (smokes < 2){
                cd++;
            }

            if (cd == regen) {
                smokes++; 
                cd =0;
            }

            if (timer == calls[comm]) {
                if (smokes > 0){
                    smokes--;
                    comm++;
                
                }
                else{ 
                    clutch = false;
                }
            }
         }
        if (clutch ==  true){
            cout << "YES" << endl;
        }

        else {
            cout << "NO" << endl; 
        }
    }

 


	 return 0;
}

