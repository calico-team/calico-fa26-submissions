
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, R;
        cin >> N >> R;

        int cargas = 2;
        int esp = 0;
        int sig = 0;
        bool posible = true;

        for(int i = 0; i < N; i++) {
            int t;
            cin >> t;

            while(esp > 0 && sig <= t) {
                cargas++;
                esp--;
                sig += R;
            }

            if(cargas == 0) {
                posible = false;
            }else {
                cargas--;

                if (esp == 0) {
                    sig = t + R;
                }

                esp++;
            }
        }

        cout << (posible ? "YES" : "NO") << '\n';
    }
}
