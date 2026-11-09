#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, k;
    cin>>n>>k;
    int x,y,z;
    string d;
    vector<vector<int>> north(2*1e5+1, vector<int>(0));
    vector<vector<int>> east(2*1e5+1, vector<int>(0));
    for(int i=0; i<n; i++){
        cin>>x>>y>>z>>d;
        if(d[0]=='N'){
            north[x+y].push_back(x);
        }else{
            east[x+y].push_back(x);
        }
    }
    int sum=0;
    for(int i=0; i<=200000;i++){
        sort(north[i].begin(), north[i].end());
        for(auto &j: east[i]){
           auto r=upper_bound(north[i].begin(), north[i].end(), j+k-1);
           auto l=lower_bound(north[i].begin(), north[i].end(),j);
           sum+=(r-l);
         }
    }
    cout<<n*k-sum<<"\n";
}


signed main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}