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
            long long A;
            cin >> A;

            while (charges < 2 && nextRecharge <= A) {
                charges++;

                if (charges < 2) {
                    nextRecharge += R;
                }
            }

            if (charges > 0) {
                if (charges == 2) {
                    nextRecharge = A + R;
                }

                charges--;
            } else {
                possible = false;
            }
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }

    return 0;
}
