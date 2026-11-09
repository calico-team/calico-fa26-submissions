#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, R;
        cin >> N >> R;

        int charges = 2;
        long long nextRecharge = 0;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long requestTime;
            cin >> requestTime;
            if (!possible) {
                continue;
            }
            while (charges < 2 && nextRecharge <= requestTime) {
                charges++;
                nextRecharge += R;
            }
        if (charges == 0) {
                possible = false;
                continue;
            }
            if (charges == 2) {
                 nextRecharge = requestTime + R;
            }
            charges--;
        }
        cout << (possible ? "YES" : "NO") << '\n';
    }
       return 0;
}