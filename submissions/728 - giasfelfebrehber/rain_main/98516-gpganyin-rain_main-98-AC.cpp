#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll=long long;using pii=pair<int,int>;using pll=pair<ll,ll>;
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define fi first
#define se second
#define int long long
const ll INF=1e18;const int MOD=1e9+7;
void fast_io(){ios::sync_with_stdio(false);cin.tie(nullptr);}

void solve() {
    int n,k;cin>>n>>k;
    vector<int>x(n),y(n),z(n),ans;
    vector<char>d(n);
    vector<vector<int>> v;
    int hmax=0;;    
    for(int i=0;i<n;i++){cin>>x[i]>>y[i]>>z[i]>>d[i];hmax=max(hmax,z[i]);v.pb({x[i]+y[i],x[i],d[i],-z[i],i});}
    sort(all(v));

    vector<int>freq(hmax+1,0);
    for(int i=0;i<n;i++){
        if(!(i>0&&v[i][0]==v[i-1][0]&&v[i][1]==v[i-1][1]&&v[i][2]==v[i-1][2])){ans.pb(v[i][4]);};
    }
    int l=0,cnt=0;
    int res=ans.size()*k;
    for(int r=0;r<ans.size();r++){
        while(l<r){
            if(x[ans[l]]+y[ans[l]]==x[ans[r]]+y[ans[r]]&&x[ans[r]]-x[ans[l]]<k){break;}
            if(d[ans[l]]=='E'){
                cnt--;
                freq[z[ans[l]]]--;
            }
            l++;
        }
        if(d[ans[r]]=='E'){
            cnt++;
            freq[z[ans[r]]]++;
        } else{
            res-=cnt-freq[z[ans[r]]];
        }
    }
    cout<<res<<"\n";
}

signed main() {
    fast_io();

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}