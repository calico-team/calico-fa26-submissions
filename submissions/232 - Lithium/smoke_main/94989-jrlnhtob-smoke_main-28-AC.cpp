#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> v(n + 1);
    bool ans = true;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int t1 = 0, t2 = 0;
    for (int i = 0; i < n; i++) {
        if (t1 <= v[i]) {
            t1 = v[i] + r;
        }
        else if (t2 <= v[i]) {
            t2 = max(t1 + r, v[i] + r);
        }
        else {
            ans = false;
        }
    }
    if (ans) cout << "yes\n";
    else cout << "no\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
}