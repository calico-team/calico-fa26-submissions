#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int n,k;
    cin>>n>>k;
    vector<char>characters(k);
    vector<string>answers(n);
    for(int i=0;i<k;i++){
        cin>>characters[i];
    }
    string ans;
    for(int i=0;i<n;i++)ans.push_back('_');
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            cout<<characters[i];
        }
        cout<<endl;
        string curr;
        cin>>curr;
        if(curr=="CORRECT"){
            return;
        }
        for(int j=0;j<n;j++){
            if(curr[j]!='_'){
                ans[j]=curr[j];
            }
        }
    }
    cout<<ans<<endl;
    cin>>ans;
}
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t=1;
    cin>>t;
    while(t--)solve();
}