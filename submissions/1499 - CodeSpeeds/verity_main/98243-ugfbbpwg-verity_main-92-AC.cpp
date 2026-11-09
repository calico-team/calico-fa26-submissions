#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc=1;
    cin>>tc;
    auto solve=[&]()->void{
        int n;
        int k;
        cin>>n>>k;
        vector<char> a(k);
        for(int i=0;i<k;i++){
            cin>>a[i];
        }
        string q(n,'?');
        for(int i=0;i+1<k;i++){
            string output(n,a[i]);
            cout<<output<<"\n";
            cout.flush();
            string w;
            cin>>w;
            if(w=="CORRECT"){
                return;
            }
            for(int j=0;j<n;j++){
                if(w[j]==a[i]){
                    q[j]=a[i];                
                }
            }
        }
        for(int i=0;i<n;i++){
            if(q[i]=='?'){
                q[i]=a.back();
            }
        }
        string output=q;
        cout<<output<<"\n";
        cout.flush();
        string w;
        cin>>w;
        return;
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}