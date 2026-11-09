// SAY REX

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ul = unsigned long;
using ld = long double;

void solve() {
    ll n, k;
    cin >> n >> k;
    string pos = "";
    for (ll i = 0; i < k; ++i) {
        char x;
        cin >> x;
        pos += x;
    }
    vector<char> ans(n, '_');
    for (ll i = 0; i < k; ++i) {
        string x = "";
        for (ll j = 0; j < n; ++j) {
            x += pos[i];
        }
        cout << x << '\n';
        string input;
        cin >> input;
        if (input == "CORRECT") {
            return;
        }
        for (ll j = 0; j < n; ++j) {
            if (input[j] != '_') {
                ans[j] = input[j];
            }
        }
    }
    for (char &x: ans) {
        cout << x;
    }
    cout << '\n';
    string input;
    cin >> input;
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}
