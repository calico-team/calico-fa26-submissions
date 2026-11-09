// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin>>t;
    while(t--){
        int n,r;
        cin>>n>>r;
        vector<int> v(n);
        for(int i=0;i<n;i++)cin>>v[i];
        int smoke1=v[0];
        int smoke2=-1;
        bool possible=true;
        for(int i=1;i<n;i++){
            if(v[i]-smoke1<r){
                if(smoke2==-1||v[i]-smoke2>=r+10){
                    smoke2=v[i];
                }
                else {
                    possible=false;
                    break;
                }
                
            }
            else{
                smoke1=v[i];
            }
        }

        //for(int i=v[0];i<v[n-1];i++){
            
        
        if(possible){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }

    }
}
