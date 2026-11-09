#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        int R[20005], C[20005], P[20005];
        for (int i = 0; i < Q; i++)
            cin >> R[i] >> C[i] >> P[i];

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                int ans = 0;
                for (int i = Q - 1; i >= 0; i--) {
                    int d = (r - R[i]) * (r - R[i]) + (c - C[i]) * (c - C[i]);
                    if (d <= P[i] * P[i]) {
                        ans = P[i] * P[i] - d + 1;
                        break;
                    }
                }
                cout << ans << " ";
            }
            cout << endl;
        }
    }
}