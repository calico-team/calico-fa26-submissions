#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;

    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool check = true;

    int smoke = 2;
    int recharge;

    for (int i = 0; i < n; i++) {
        // cout << a[i] << " " << smoke << " " << recharge << "\n";

        if (smoke == 2) {
            smoke = 1;
            recharge = a[i];
            continue;
        }

        if (smoke == 1) {
            if (a[i] >= recharge + r) {
                recharge = a[i];
            } else {
                smoke = 0;
            }

            continue;
        }

        if (a[i] >= recharge + 2 * r) {
            recharge = a[i];
            smoke = 1;
        } else if (a[i] >= recharge + r) {
            recharge = a[i];
        } else {
            check = false;
            break;
        }
    }

    if (check) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}