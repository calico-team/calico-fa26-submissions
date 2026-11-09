#include<bits/stdc++.h>
using namespace std;

int p[10005],d[10005];
int dep(int i){
    if(i==0){
        return 0;
    }
    if(d[i]==0){
        d[i]=dep(p[i])+1;
    }
    return d[i];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while(t--){
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++){
            cin>>p[i];
            d[i]=0;
        }
        int cnt[50005]={};
        for(int i=1;i<=n;i++){
            cnt[dep(i)]++;
        }
        int ans=0;
        for(int i=1;i<=m;i++){
            int x=cnt[i];
            if(x>k){
                x=k;
            }
            ans+=x;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
