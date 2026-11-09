#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD=1e9+7,MAXF=2000005,INF=1e18,INV=5e8+4;

string query(string s){
    cout<<s<<endl;
    string res;
    if(!(cin>>res)) exit(0);
    return res;
}

void solve(){
    int n,k;cin>>n>>k;
    vector<char> a(k);
    for(int i=0;i<k;i++) cin>>a[i];
    string ans="";
    for(int i=0;i<n;i++) ans+=" ";
    for(int i=0;i<k;i++){
        string guess="";
        for(int j=0;j<n;j++){
            guess+=a[i];
        }
        string feed=query(guess);
        if(feed=="CORRECT") return;
        for(int j;j<n;j++){
            if(feed[j]!='_') ans[j]=feed[j];
        }
    }
    string yay=query(ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin>>t;
    while(t--) solve();

}