#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vll vector<ll>
#define vvl vector<vll>
#define pll pair<ll,ll>
#define bismillah ios_base::sync_with_stdio(false); 
#define medal cin.tie(NULL);
const ll INF = 4e18;
#define pb push_back
#define fi first
#define se second
#define vpll vector<pll>
const ll mod = 1e9 + 7;
const ll maxn = 1e6 + 7;
#define eb emplace_back
const ll maxlog = 20;




void solve(){
    ll n,r; cin >> n >> r;
    ll cnt1 = 0;
    ll cnt2 = 0;

    vll v(n + 1);
    v[0] = 0;


    for(ll i = 1; i <= n; i++) cin >> v[i];

    for(ll i = 1; i <= n; i++){
     if(cnt1 == 0) cnt1 -= r;
     else if(cnt2 == 0) cnt2 -= r;
     else {
        cout << "NO\n";
        return;
     }

     cnt1 = min(cnt1 + (v[i] - v[i - 1]), 0ll);
     cnt2 = min(cnt2 + (v[i] - v[i - 1]), 0ll);
    }

    cout << "YES\n";
}


int main(){
    bismillah medal
    ll t; cin >> t;
    while(t--)solve();
}