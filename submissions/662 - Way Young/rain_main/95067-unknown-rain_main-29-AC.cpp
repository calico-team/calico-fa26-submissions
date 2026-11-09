#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fu(i,a,b) for(int i=(a);i<=(b);i++)
#define fd(i,a,b) for(int i=(a);i>=(b);i--)
#define V vector 
#define sz(x) (int)(x).size()

void solve() {
    int n,k;
    cin>>n>>k;
    V<array<int,2>> info;

    map<int, V<int> > diag;

    fu(i,1,n) {
        int x,y,z;
        char d;
        cin>>x>>y>>z>>d;
        if(d == 'E') {
            
            diag[x+y].push_back(x);
        } else {
            info.push_back({x,y});
        }
    }
    for(auto [key,val]:diag) {
        sort(diag[key].begin(),diag[key].end());
    }
    int ans=k*n; // minus intersections
    for(auto [x1,y1]:info) {
        if(diag[x1+y1].empty()) {
          //  cout<<x1+y1<<'\n';
            continue;
        }
        int hi=upper_bound(diag[x1+y1].begin(), 
    diag[x1+y1].end(), x1) - diag[x1+y1].begin() - 1;
   // cout<<hi<<'\n';
        int lo=lower_bound(diag[x1+y1].begin(),
    diag[x1+y1].end(), x1-k+1) - diag[x1+y1].begin();
   // cout<<lo<<'\n';
        if(lo<=hi) {
            ans -= (hi-lo+1);
        }
    }
    cout<<ans<<'\n';
    
}
signed main() {
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}