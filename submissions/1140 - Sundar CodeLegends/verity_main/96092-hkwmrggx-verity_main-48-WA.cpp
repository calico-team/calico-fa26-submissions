#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;

void solve(){
    int n,k;cin >> n >> k;
    vector<char> t;
    for(int i = 0 ; i < k ; i ++){
        char c;cin >> c;
        t.push_back(c);
    }
    string ans(n, ' ');
    for(auto c : t){
        string s;
        for(int i = 0 ; i < n ; i ++)s += c;
        cout << s << endl;
        string tt;cin >> tt;
        for(int i = 0 ; i < n ; i ++){
            if(tt[i] != '_'){
                ans[i] = c;
            }
        }
    }
    
    cout << ans << endl;
    string u;
    cin >> u;
    cout.flush();
}
signed main(){
    // ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    // cin.tie(0), cout.tie(0);
    // cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
