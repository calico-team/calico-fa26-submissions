#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin>> tc;
    while (tc--) {
        int n; ll r;
        cin >> n>>r;
        
        vector<ll> a(n);
        for (int i =0; i < n; i++) cin >> a[i];

        int cur =2;
        ll nxt =-1;
        bool ok =1;

        // terpaksa simulasikan token bucket pake array biar gampang di-trace
        for (int i =0; i < n; i++) {
            ll x = a[i];
            if (!ok) continue;

            // compact while jadi for loop satu baris biar AST berubah total
            for (; cur <2 &&nxt <= x; cur++, nxt += r);

            if (!cur) {
                ok =0;
                continue;
            }

            if (cur ==2) nxt = x + r;
            cur--;
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}