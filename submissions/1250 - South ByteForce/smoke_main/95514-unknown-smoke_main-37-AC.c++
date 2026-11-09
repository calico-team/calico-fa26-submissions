#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    for (int test = 0; test < T; test++) {
        int N, R;
        cin >> N >> R;

        long long ready1 = 0;
        long long ready2 = 0;

        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long a;
            cin >> a;

            if (possible == false) {
                continue;
            }

            if (ready1 > ready2) {
                long long temp = ready1;
                ready1 = ready2;
                ready2 = temp;
            }

            if (ready1 <= a) {
                long long start = a;
                if (ready2 > a) {
                    start = ready2;
                }
                ready1 = start + R;
            } else {
                possible = false;
            }
        }

        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}