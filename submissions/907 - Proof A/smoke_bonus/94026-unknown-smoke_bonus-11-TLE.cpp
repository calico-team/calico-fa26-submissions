#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int test;
    cin >> test;
    for (int tc = 0; tc < test; tc++) {
        int n, r;
        cin >> n >> r;

        int as[n];

        for (int i = 0; i < n; i++) {
            cin >> as[i];
        }

        if (n <= 2) {
            cout << "YES" << endl;
            continue;
        }

        int prev1 = as[0];
        int prev2 = max(as[0]+r, as[1]);
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
