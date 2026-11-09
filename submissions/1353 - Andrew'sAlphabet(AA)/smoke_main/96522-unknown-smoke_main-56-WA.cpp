#include <bits/stdc++.h>
using namespace std;

int main(){
    int T; // number of cases
    cin >> T;
    for (int i=0;i<T;i++){
        bool accepted = true;
        bool completed = false;
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


        for (int i=0;i<N;i++){
            completed = false;
            while (completed==false){
                if (times[i]>=charge1[i]&&times[i]!=charge2[i]){
                    completed=true;
                } else if (times[i]!=charge1[i]&&times[i]>=charge2[i]){
                    completed=true;
                }
                if (completed==false){
                    completed = true;
                    accepted = false;
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