#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

void solve(){
    int t;
    cin>>t;
    while(t--){
        int n,r;
        cin>>n>>r;
        int cnt=2; 
        int next=0;
        bool ok=1;

        forn(i,0,n){
            int a;
            cin>>a;
            if(!ok) continue;
            //bludtooeasy!
            while(cnt<2 && next<=a){
                cnt++;
                next+=r;
            }
            if(cnt==0){
                ok=!ok;
                continue;
            }
            if(cnt==2){
next=a+r;
            } 
            cnt--;
        }
        if(ok) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}