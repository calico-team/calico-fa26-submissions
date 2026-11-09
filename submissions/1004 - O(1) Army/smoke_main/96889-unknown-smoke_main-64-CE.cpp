#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, charges = 2;
        long long recharge, next = 0;
        bool possible = true;
        cin >> n >> recharge;
        while (n--) {
            long long time;
            cin >> time;
            if (!possible) continue;
            while (charges < 2 && next <= time) {
                ++charges
                next += recharge;
            }
            if (charges == 0) {
                possible = false;
                continue;
            }
            if (charges == 2) next = time + recharge;
            --charges;
        }
        cout << (possible ? "YES\n" : "NO\n");
    }
}
