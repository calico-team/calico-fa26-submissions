#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    int n;
    ll r;
    if (!(cin>> n>> r)) return;
    
    vector<ll> a(n);
    for (int i =0; i <n;i++) cin >> a[i];

    ll slot1 = -1, slot2 = -1; 
    int charges = 2;
    bool ok =true;

    for (int i = 0; i < n; i++) {
        ll t = a[i];

        // update status recharge dulu sebelum request diproses
        if (charges < 2 && slot1 != -1 && t >= slot1) {
            charges++;
            slot1 =slot2; 
            slot2 = -1;
            if (charges < 2 && slot1 != -1 && t >= slot1) {
                charges++;
                slot1 = -1;
            }
        }

        // ga ada charge tersisa -> bismillah ga WA/TLE, langsung tembak NO
        if (charges <=0) {
            ok= false;
            break;
        }
        charges--;
        ll ready_time = t + r;

        if (slot1 == -1) {
            slot1= ready_time;
        } else {
            slot2 =slot1 + r; 
        }
    }

    if (ok) cout <<"YES\n";
    else cout << "NO\n";
}

int main() {
   
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}