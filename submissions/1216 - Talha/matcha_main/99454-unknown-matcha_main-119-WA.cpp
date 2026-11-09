#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int> l, vector<int> r) {
    if (n == 1) return r[0];
    int b = -1;
    for (int i = 0; i < n; i++)
        if (l[i] != r[i]) b = max(b, 31 - __builtin_clz(l[i] ^ r[i]));
    if (b == -1) {
        int x = 0;
        for (int v : l) x ^= v;
        return x;
    }
    int sh = b + 1, fx = 0;
    for (int v : l) fx ^= (v >> sh) << sh;
    return fx | ((1 << sh) - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> l(n), r(n);
        for (int &x : l) cin >> x;
        for (int &x : r) cin >> x;
        cout << solve(n, l, r) << "\n";
    }
}
