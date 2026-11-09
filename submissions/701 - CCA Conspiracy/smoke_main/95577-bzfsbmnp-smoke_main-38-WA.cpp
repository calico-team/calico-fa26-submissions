#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int t;
    cin>>t;
    while(t--){
        int N;
        int R;
        cin>>N>>R;
        vector <int> arr(N);
        for(int i = 0; i<N; i++){
            cin>>arr[i];
        }
        bool work = true;
        int charge1=0;
        int charge2=0;
        for(int i = 0; i<N-1; i++){
            if(charge1!=0 && charge2!=0){
                work=false;
                break;
            }
            if(charge1==0){
                charge1=R;
            }
            else if(charge2==0){
                charge2=R;
            }
            int time=arr[i+1]-arr[i];
            if(charge1-time>=0){
                charge1-=time;
                time=0;
            }
            else{
                time-=charge1;
                charge1=0;
                charge2=max(0ll, charge2-time);
            }
            
        }
        if(charge1!=0 && charge2!=0){
                work=false;
        }
        if(work){
            cout<<"YES"<<"\n";
        }
        else{
            cout<<"NO"<<"\n";
        }
    }
}
