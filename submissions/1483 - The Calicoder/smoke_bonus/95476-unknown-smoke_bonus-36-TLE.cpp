// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, R;
        cin >> N >> R;

        int charges = 2;
        long long nextRecharge = -1;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long A;
            cin >> A;

            while (nextRecharge != -1 && nextRecharge <= A) {
                charges++;

                if (charges == 2) {
                    nextRecharge = -1;
                } else {
                    nextRecharge += R;
                }
            }

            if (charges == 0) {
                possible = false;
            } else {
                charges--;

                if (nextRecharge == -1) {
                    nextRecharge = A + R;
                }
            }
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
}
