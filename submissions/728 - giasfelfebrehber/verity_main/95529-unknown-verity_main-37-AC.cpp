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
    vector<char>a(k);
    for(int i=0;i<k;i++)cin>>a[i];
    string ans(n,' ');
    for(char c:a){
        string guess(n, c);
        cout<<guess<<endl;
        string s;cin>>s;
        if(s=="CORRECT"){return;}
        for(int i=0;i<n;i++){
            if(s[i]==c){ans[i]=c;}
        }
    }
    cout<<ans<<endl;
    string s;cin>>s;
    return;
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