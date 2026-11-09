// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int> X(N), Y(N), Z(N);
        vector<char> D(N);

        for (int i = 0; i < N; i++) {
            cin >> X[i] >> Y[i] >> Z[i] >> D[i];
        }

        long long rain = 0;

        for (int day = 0; day < K; day++) {

            for (int i = 0; i < N; i++) {
                bool blocked = false;

                for (int j = 0; j < N; j++) {
                    if (X[i] == X[j] &&
                        Y[i] == Y[j] &&
                        Z[j] > Z[i]) {
                        blocked = true;
                        break;
                    }
                }

                if (!blocked) {
                    rain++;
                }
            }

            for (int i = 0; i < N; i++) {
                if (D[i] == 'E') {
                    X[i]++;
                } else {
                    Y[i]++;
                }
            }
        }

        cout << rain << endl;
    }
}
