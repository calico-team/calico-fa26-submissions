
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        long long R;
        cin >> N >> R;

        int charges = 2;
        long long nextRecharge = 0;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long t;
            cin >> t;

            if (!possible)
                continue;

            // Check completed recharges
            while (charges < 2 && t >= nextRecharge) {
                charges++;

                if (charges < 2)
                    nextRecharge += R;
            }

            if (charges == 0) {
                possible = false;
            }
            else {
                // Start recharging if both were full
                if (charges == 2) {
                    nextRecharge = t + R;
                }

                charges--;
            }
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
