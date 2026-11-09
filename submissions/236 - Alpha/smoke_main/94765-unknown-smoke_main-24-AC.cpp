#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll r, f = 0, g = 0;
        cin >> n >> r;
        string ans = "YES";
        while (n--) {
            ll x;
            cin >> x;
            if (f > x) ans = "NO";
            else {
                ll h = max(x, g) + r;
                f = g, g = h;}}
        cout << ans << "\n";}}