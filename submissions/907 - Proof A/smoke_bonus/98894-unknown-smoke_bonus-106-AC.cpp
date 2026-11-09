#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test;
    cin >> test;
    ll as[(int) 1e5];
    for (int tc = 0; tc < test; tc++) {
        ll n, r;
        cin >> n >> r;

        for (int i = 0; i < n; i++) {
            cin >> as[i];
        }

        if (n <= 2) {
            cout << "YES" << endl;
            continue;
        }

        ll prev1 = as[0];
        ll prev2 = max(as[0]+r, as[1]);
        bool done = false;

        for (int i = 2; i < n; i++) {
            if (as[i] < (prev1 + r)) {
                cout << "NO" << endl;
                done = true;
                break;
            }

            prev1 = prev2;
            prev2 = max(as[i], prev1 + r);
        }
        if (!done) {
            cout << "YES" << endl;
        }



    }



}
