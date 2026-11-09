#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n,r;cin>>n>>r;
    vector<int>a(n);
    for(int i=0;i<n;++i){
        cin>>a[i];
    }
    long long cd1=0,cd2=0;
    int nsmoke=0;
    for(int i=0;i<n;++i){
        long long time=a[i];
        if(cd1!=-1&&time>=cd1){
            ++nsmoke;
            cd1=-1;
        }
        if(cd2!=-1&&time>=cd2){
            ++nsmoke;
            cd2=-1;
        }
        if(cd1==-1)
            swap(cd1,cd2);
        if(nsmoke>0){
            --nsmoke;
            cd2=max(cd1,time)+r;
        } else{
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";

}
int main(){
    int t;cin>>t;while(t--){
        solve();
    }
}
