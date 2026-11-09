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

    int smoke_hp = 2*r;
    int start_recharge;
    
    for (int i = 0; i < n; i++) {
        // cout << a[i] << " " << smoke_hp << " " << start_recharge << "\n";

        if (smoke_hp < 2*r) {
            smoke_hp = min(2*r, smoke_hp + a[i] - start_recharge);
        }

        if (smoke_hp == 2*r) {
            smoke_hp -= r;
            start_recharge = a[i];
            continue;
        }

        if (smoke_hp - r < 0) {
            check = false;
            break;
        }

        smoke_hp -= r;
        start_recharge = a[i];
    }

    // for (int i = 0; i < n; i++) {
    //     // cout << a[i] << " " << smoke << " " << recharge << "\n";

    //     if (smoke == 2) {
    //         smoke = 1;
    //         recharge = a[i];
    //         continue;
    //     }

    //     if (smoke == 1) {
    //         if (a[i] >= recharge + r) {
    //             recharge = a[i];
    //         } else {
    //             smoke = 0;
    //         }

    //         continue;
    //     }

    //     if (a[i] >= recharge + 2 * r) {
    //         recharge = a[i];
    //         smoke = 1;
    //     } else if (a[i] >= recharge + r) {
    //         recharge = a[i];
    //     } else {
    //         check = false;
    //         break;
    //     }
    // }

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