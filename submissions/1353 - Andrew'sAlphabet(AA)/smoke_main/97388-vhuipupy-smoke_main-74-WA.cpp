#include <bits/stdc++.h>
using namespace std;

int main(){
    int T; // number of cases
    cin >> T;
    for (int i=0;i<T;i++){
        bool accepted = true;
        bool completed = false;
        bool recharge1;
        bool recharge2;
        int N; // number of requests
        int seconds; //seconds per recharge
        
        
        cin >> N >> seconds;
        int req; // request time
        vector<int> times(N);
        for(int i=0;i<N;i++){
            cin >> req;
            times[i] = req;
        }


        int time1;
        int time2;
        time1 = times[0];
        time2 = times[1];
        vector<int> charge1(N);
        vector<int> charge2(N);
        charge1[0] = time1;
        charge2[0] = time2;
        for (int i=0;i<N-1;i++){
            charge1[i+1] = charge1[i]+seconds;
        }
        for (int i=0;i<N-1;i++){
            charge2[i+1] = charge2[i]+seconds;
        }
        recharge1 = false;
        recharge2 = false;

        for (int i=0;i<N;i++){
            completed = false;
            while (completed==false){
                if (times[i]<charge1[i]&&times[i]<charge2[i]){
                    recharge1 = true;
                    recharge2 = true;
                    accepted = false;
                    completed = true;
                }
                if (times[i]>=charge1[i]&&times[i]!=charge2[i]){
                    completed=true;
                    recharge1 = false;
                } else if (times[i]!=charge1[i]&&times[i]>=charge2[i]){
                    completed=true;
                    recharge2 = false;
                }
            }
        }

        if (accepted==true){
            cout << "YES" << endl;
        }
        if (accepted==false){
            cout<< "NO" << endl;
        }
 
    }    
    return 0;
}