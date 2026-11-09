#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int n;
    ll r;
    cin >> n >> r;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int c = 2;
    ll nextr = -1;
    for (ll t : a) {
        while (c<2 && nextr<=t) {
            c++; // haha c++ reference
            if (c < 2) {
                nextr += r;
            }
        }

        if (c == 0) {
            cout << "NO\n";
            return;
        }
        if (c == 2) {
            nextr = t+r;
        }
        c--;
    }
    cout << "YES\n";
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}