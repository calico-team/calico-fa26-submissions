#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int maxn=1e5+7;
int n,r,ans=0;
signed main() {
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--) {
        cin>>n>>r;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        if(n<=2){
            cout<<"YES"<<endl;
            continue;
        }
        int process=a[1]-a[0];
        bool flag=0;
        for(int i=2;i<n;i++) {
            process+=a[i]-a[i-1];
            process=min(process,2*r);
            if(process>r){
                process-=r;
            }else{
                flag=1;
                cout<<"NO"<<endl;
                break;
            }
        }
        if(flag) continue;
        cout<<"YES"<<endl;
    }
    return 0;
}