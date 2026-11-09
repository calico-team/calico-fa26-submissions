#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; int r;
    cin >> n >> r;
    int charge = 2;

    int recharge = 0;
    bool ans = true;

    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;

        if(ans) {
            while(charge < 2 && recharge <= a) {
                charge++;
                recharge += r;
            }
            if(charge == 0) {
                ans = false;
            }
            else {
                if(charge == 2) {
                    recharge = a + r;
                }
                charge--;
            }

        }
    }

    if(ans) {
        cout << "YES" << "\n";
    }
    else {
        cout << "NO" << "\n";
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t-- > 0) {
        solve();
    }

    return 0;
}