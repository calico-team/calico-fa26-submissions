#include <bits/stdc++.h>
using namespace std;


int main() {
    int k;
    cin>>k;
    for(int i=0; i<k; i++){
        int n, r;
        bool flag=1;
        cin>>n>>r;
        int recharge=0, charges=2, last=0;
        for(int j=0; j<n; j++){
            int a;
            cin>>a;
            if(flag==1){
                recharge+=a-last;
                if(charges==2) recharge=0;
                if(recharge>=r){
                    recharge-=r;
                    charges++;
                    if(recharge>=r&&charges==1) charges++;
                    if(charges==2) recharge=0;
                }
                if(charges>=1) charges--;
                else flag=0;
            }
        }
        if(flag==1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}