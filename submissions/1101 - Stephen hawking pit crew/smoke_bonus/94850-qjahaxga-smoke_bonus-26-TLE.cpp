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
        ll cnt=2, nxt=0, nxtt=0;
        bool b=true;
        for(ll i=0; i<n; i++) {
            while(nxt>0 && nxtt<=v[i]) {
                cnt++;
                nxt--;
                nxtt+=r;
            }
            if(cnt==0) {
                b=false;
                break;
            }
            cnt--;
            if(nxt==0) nxtt=v[i]+r;
            nxt++;
        }
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}