#include<bits/stdc++.h>
using namespace std;
#define int long long 
#pragma GCC optimize("O3,unroll-loops")

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int tc; cin>>tc;
    while(tc--){
        int n,r;cin>>n>>r;
        int a[n+1];
        for(int q=1;q<=n;q++)cin>>a[q];

        int x=0,y=0;
        bool oke=true;

        for(int q=1;q<=n;q++){
            if(x>y)swap(x,y);

            if(x<=a[q]){
                x=max(a[q]+1+r,y+1+r);
            }
            else{
                oke=false;
            }
        }

        if(oke){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
}