#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll n, r;
        cin >> n >> r;
        vector<ll> a(n);
        bool poss = true;
        for (auto &x : a) {
            cin >> x;
        }
        for (int i = 1; i < n; i++) {
            if (r > abs(a[i - 1] - a[i])) {
                poss = false;
            }
        }
        cout << (poss ? "Yes" : "No") << '\n';

    }

    return 0;
}