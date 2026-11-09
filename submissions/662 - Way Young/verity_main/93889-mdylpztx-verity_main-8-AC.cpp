#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n,k;
    cin>>n>>k;
    vector<char> a(k);
    for(char& c:a){
        cin>>c;
    }
    string ans(n,a[0]);
    for(int i=1;i<k;i++){
        string s(n,a[i]);
        cout<<s<<endl;
        string t;
        cin>>t;
        if(t=="CORRECT"){
            return ;
        }
        for(int j=0;j<n;j++){
            if(t[j]!='_'){
                ans[j]=t[j];
            }
        }
    }
    cout<<ans<<endl;
    string t;
    cin>>t;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}