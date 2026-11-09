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
                charge2=charge1+R;
            }
            int time=arr[i+1]-arr[i];
            charge1=max(charge1-time,0ll);
            charge2=max(charge2-time,0ll);
            
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
