#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long K;
        cin >> N >> K;

        int X[100005];
        int Y[100005];
        char D[100005];

        for (int i = 0; i < N; i++) {
            int Z;
            cin >> X[i] >> Y[i] >> Z >> D[i];
        }

        long long ans = (long long)N * K;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (D[i] == 'E' && D[j] == 'N') {
                    if (X[i] + Y[i] == X[j] + Y[j]) {
                        if (X[j] >= X[i] && X[j] - X[i] < K) {
                            ans--;
                        }
                    }
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
