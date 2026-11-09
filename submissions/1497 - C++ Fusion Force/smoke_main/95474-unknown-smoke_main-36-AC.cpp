#include <bits/stdc++.h>
using namespace std;


int main() {
    int k;
    cin>>k;
    for(int i=0; i<k; i++){
        int n, r;
        bool flag=1;
        cin>>n>>r;
        vector<int> v;
        v.push_back(0);
        for(int j=0; j<n; j++){
            int a;
            cin>>a;
            v.push_back(a);
        }
        int recharge=0, charges=2;
        for(int j=1; j<v.size(); j++){
            if(flag==1){
            recharge+=v[j]-v[j-1];
            if(charges==2) recharge=0;
            if(recharge>=r){
                recharge-=r;
                charges++;
                if(recharge>=r&&charges==1){
                    charges++;
                }
                if(charges==2) recharge=0;
            }
            if(charges>=1){
                charges--;
            }
            else {
                flag=0;
                cout<<"NO"<<endl;}
            }
        }
        if(flag==1) cout<<"YES"<<endl;
    }
}