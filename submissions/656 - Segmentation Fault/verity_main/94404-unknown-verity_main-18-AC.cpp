#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<char> a(k);
    string s(n, '?');
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    for (int j = 0; j < k; j++) {
        string guess = s, r;
        for (int i = 0; i < n; i++) {
            if (guess[i] == '?') {
                guess[i] = a[j];
            }
        }

        cout << guess << endl;
        cin >> r;
        if (r == "CORRECT") return;
        for (int i = 0; i < n; i++) {
            if (r[i] != '_') {
                s[i] = r[i];
            }
        }
    }
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