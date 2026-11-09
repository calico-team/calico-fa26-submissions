#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;

void solve(){
    int n,r;cin >> n >> r;
    vector<int> v(n + 1);
    for(int i = 1 ; i <= n ; i ++)cin >> v[i];
    bool s1 = false, s2 = false;
    int p1 = 0, p2 = 0;
    s1 = true;
    p1 = v[1] + r;
    for(int i = 2 ; i <= n ; i ++){
        // cout << i << ' ' << p1 << ' ' << p2 << endl;
        if(p1 <= v[i] and s1){
            s1 = false;
        }
        if(p2 <= v[i] and s2){
            s2 = false;
        }
        if(i == 4){
            // cout << s1 << ' ' << s2 << ' ' << p2 << endl;
        }
        if(!s1){
            s1 = true;
            p1 = v[i] + r;
        }
        else if(!s2){
            s2 = true;
            p2 = max(p1,v[i]) + r;
        }
        else{
            cout << "NO" << '\n';return;
        }
    }
    cout << "YES" << '\n';
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
