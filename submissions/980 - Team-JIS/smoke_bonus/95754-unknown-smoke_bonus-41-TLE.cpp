
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, R;
        cin >> N >> R;

        vector<int> A(N);

        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        int cargas = 2;
        queue<int> recarga;

        bool posible = true;

        for (int i = 0; i < N; i++) {

            while (!recarga.empty() && recarga.front() <= A[i]) {
                cargas++;
                recarga.pop();
            }

            if (cargas == 0) {
                posible = false;
                break;
            }

            cargas--;

            int tiemp;

            if (recarga.empty()) {
                tiemp = A[i] + R;
            } else {
                tiemp = recarga.back() + R;
            }

            recarga.push(tiemp);
        }

        cout << (posible ? "YES" : "NO") << '\n';
    }

    return 0;
}
