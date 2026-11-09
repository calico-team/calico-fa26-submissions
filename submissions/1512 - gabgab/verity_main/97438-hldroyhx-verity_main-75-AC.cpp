#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<char> a(k);
        for (auto &x : a) {
            cin >> x;
        }
        string res = "";
        string out(n, '_');
        for (int ii = 0; ii < k; ii++) {
            string guess = out;
            for (int i = 0; i < n; i++) {
                if (guess[i] == '_') {
                    guess[i] = a[ii];
                }
            }
            cout << guess << endl;
            cin >> res;
            if (res == "CORRECT") {
                break;
            }
            for (int iii = 0; iii < n; iii++) {
                if (res[iii] != '_') {
                    out[iii] = res[iii];
                }
            }
        }
    }

    return 0;
}