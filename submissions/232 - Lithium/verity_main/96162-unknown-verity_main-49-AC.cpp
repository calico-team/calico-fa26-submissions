#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<char> v(k), cur(n);
    vector<bool> ans(n);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
    }
    int pos = 0;
    while (true) {
        for (int i = 0; i < n; i++) {
            if (ans[i] == 0) {  
                cout << v[pos];
            }
            else cout << cur[i];
        }
        cout << endl;
        string s;
        cin >> s;
        if (s == "CORRECT") {
            return;
        }
        for (int i = 0; i < n; i++) {
            if (s[i] != '_') {
                ans[i] = true;
                cur[i] = s[i];
            }
        }
        pos++;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}