#include "bits/extc++.h"

using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
    int arr[n];
    for(int i = 0; i<n; i++) cin>>arr[i];
    int t1=0,t2=0;
    auto incv = [&](int x) -> void {
        int spendv=min(t1,x);
        t1-=spendv;
        x-=spendv;
        t2-=min(t2,x);
    };
    bool fail=0;
    for(int i = 0; i<n; i++){
        if(i!=0){
            incv(arr[i]-arr[i-1]);
        }
        if(t1!=0 && t2!=0){
            fail=1;
            break;
        }
        if(t1!=0) swap(t1,t2);
        t1=k;
    }
    if(fail){
        cout<<"NO\n";
    }else{
        cout<<"YES\n";
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::failbit);
    int t;
    cin>>t;
    while(t--) solve();
}
