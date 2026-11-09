#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main(){
    int n,t,r;
    cin>>t;
    while(t--){
        int chance=2;
        cin>>n>>r;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++){
            if(a[i]/r-i<=0&&a[i]%r!=0)chance--;
        }
        if(chance<0)cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}