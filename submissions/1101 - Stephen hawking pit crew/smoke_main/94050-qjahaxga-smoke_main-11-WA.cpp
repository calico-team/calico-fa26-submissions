#include <bits/stdc++.h>
#define f first
#define s second
using ll=long long;
using ull=unsigned long long;
using namespace std;
int main() {
    ll t; cin >> t;
    while(t--) {
        ll n, r; cin >> n >> r;
        vector<ll> v(n);
        for(ll i=0; i<n; i++) cin >> v[i];
        ll nxt=0;
        if(n>=2) nxt=v[1]+r;
        else nxt=0;
        bool b=true;
        for(ll i=2; i<n; i++) {
            if(v[i]<nxt) {
                b=false;
                break;
            }
            nxt=v[i]+r;
        }
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}