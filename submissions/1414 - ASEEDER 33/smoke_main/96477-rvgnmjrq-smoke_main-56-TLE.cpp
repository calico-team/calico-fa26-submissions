#include<bits/stdc++.h>
using namespace std;
int a[100001],f[100001];
int main(){
    freopen("1.in","r",stdin);
    int n,t,r;
    cin>>t;
    while(t--){
        bool flag=1;
        cin>>n>>r;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++){
            if(i>=2&&f[i-2]>a[i]){
                flag=0;
                break;
            }
            int temp=0;
            if(i>0)temp=f[i-1];
            if(a[i]>temp)f[i]=a[i]+r;
            else f[i]=temp+r;
        }
        if(flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}