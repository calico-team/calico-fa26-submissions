#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve() {
    int n, r;
    cin >> n>>r;
    
    queue<ll> q;
    bool ok =true;
    
    for (int i = 0; i < n; i++) {
        ll a;
        cin>>a;
    
        while (!q.empty() && q.front() <= a) {
            q.pop();
        }
        
        if (q.size() <2) {
            // Masukin waktu kapan smoke ini bakal ready lagi
            ll next_avail = a +r;
            if (!q.empty()) {
          
            }
            q.push(next_avail);
        } else {
            ok =false;
        }
    }
    
    if (ok) cout <<"YES\n";
    else cout<< "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >>t;
    while (t--) {
        solve();
    }
    
    return 0;
}