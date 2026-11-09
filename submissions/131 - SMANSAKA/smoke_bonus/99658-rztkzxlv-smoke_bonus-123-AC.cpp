#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; ll r;
        cin >> n >> r;
           vector<ll> q;
        bool ok = 1;
        
        for (int i = 0; i < n; i++) {
            ll a; cin>> a;
            if (!ok) continue;
            
           
            while (!q.empty() && q.front() <=a) {
                q.erase(q.begin());
            }
            if (q.size() ==2) {
                ok =0;
                continue;
            }
            
            if (q.empty()) {
                q.push_back(a +r);
            } else {
                q.push_back(q.back() +r);
            }
        }
        
        cout << (ok ? "YES\n" : "NO\n");
    }
    
    return 0;
}