#include <iostream>
#include <string>
using namespace std;

int main() {
    int matches; 
    cin >> matches; 

    for (int m = 0; m < matches; m++) {
        int pings, regen;
        cin >> pings >> regen; 

        int calls[1000];
        for (int i = 0; i < pings; i++) {
            cin >> calls[i];
        }
        
         int smokes = 2;
         int cd = 0; 
         int comm = 0;
         bool clutch = true; 

         int last_comm = calls[pings - 1];

         for (int timer = 1; timer <= last_comm; timer++){

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

