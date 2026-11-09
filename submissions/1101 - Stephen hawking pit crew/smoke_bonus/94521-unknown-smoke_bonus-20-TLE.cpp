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
        bool b=true;
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        ll cnt=2;
        for(ll i=0; i<n; i++) {
            while(!pq.empty() && pq.top()<=v[i]) {
                pq.pop();
                cnt++;
            }
            if(cnt==0) {
                b=false;
                break;
            }
            cnt--;
            if(pq.empty()) pq.push(v[i]+r);
            else pq.push((ll)pq.top()+r*(ll)pq.size());
        }
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}