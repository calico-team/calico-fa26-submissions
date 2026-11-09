#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        long long r;
        cin >> n >> r;

        int charges = 2;
        long long nextRecharge = 0;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            long long time;
            cin >> time;

            if (!possible) continue;

            // Restore charges before handling this request.
            while (charges < 2 && nextRecharge <= time) {
                charges++;
                nextRecharge += r;
            }

            if (charges == 0) {
                possible = false;
                continue;
            }

            // Using a charge from full capacity starts a new recharge.
            if (charges == 2) {
                nextRecharge = time + r;
            }
            charges--;
        }

        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
