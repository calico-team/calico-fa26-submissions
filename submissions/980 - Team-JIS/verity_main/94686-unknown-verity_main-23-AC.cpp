
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);

        for (int i = 0; i < K; i++) {
            cin >> A[i];
        }

        string cad(N, '?');

        for (int j = 0; j < K; j++) {
            string prueba(N, A[j]);

            for (int i = 0; i < N; i++) {
                if (cad[i] != '?') {
                    prueba[i] = cad[i];
                }
            }

            cout << prueba << endl;

            string acep;
            cin >> acep;

            if (acep == "CORRECT") {
                break;
            }

            for (int i = 0; i < N; i++) {
                if (acep[i] != '_') {
                    cad[i] = acep[i];
                }
            }
        }
    }

    return 0;
}
