#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD=1e9+7,MAXF=2000005,INF=1e18,INV=5e8+4;

void solve(){
    ll n,k;cin>>n>>k;
    map<int,vector<int>> east,north;
    ll cnt=0;
    for(int i=0;i<n;i++){
        int x,y,z;cin>>x>>y>>z;
        char d;cin>>d;
        if(d=='E'){
            east[x+y].push_back(x);
        } else{
            north[x+y].push_back(x);
        }
    }

    for(auto& c:east){
        int sum=c.first;
        vector<int>& ea=c.second;

        vector<int>& no=north[sum];
        sort(no.begin(),no.end());

        for(auto xe:ea){
            cnt+=distance(lower_bound(no.begin(),no.end(),xe),lower_bound(no.begin(),no.end(),xe+k));
        }

    }
    cout<<n*k-cnt<<'\n';
    
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin>>t;
    while(t--) solve();

}