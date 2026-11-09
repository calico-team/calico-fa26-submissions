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
        int r;
        cin>>n>>r;
        vector<int> a(n);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int q=0;
        int w=0;
        string output="YES";
        for(int i=0;i<n;i++){
            if(q>w){
                swap(q,w);
            }
            if(q>a[i]){
                output="NO";
                break;
            }
            q=max(a[i],w)+r;
        }
        cout<<output<<"\n";
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}