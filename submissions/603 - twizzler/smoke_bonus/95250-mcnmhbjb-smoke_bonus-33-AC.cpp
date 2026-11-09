#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long r;
        cin >> n >> r;

        int charges = 2;
        long long rec = 0;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
            if (!ok) {
                continue;
            }

            while (charges < 2 && rec <= a) {
                charges++;
                if (charges < 2) {
                    rec += r;
                }
            }

            if (charges == 0) {
                ok = false;
                continue;
            }
            if (charges == 2) {
                rec = a + r;
            }
            charges--;
        }

        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
