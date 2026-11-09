#include <iostream>
using namespace std;

int main() {
    int test;
    cin >> test;
    while (test--) {
        int n;
        long long r;
        cin >> n >> r;

        long long time[100005];
        for (int i = 0; i < n; i++) {
            cin >> time[i];
        }

        int charge = 2;
        long long kabTak[100005];
        int aage = 0, peeche = 0;
        long long lastWala = 0;
        int hoGaya = 1;

        for (int i = 0; i < n; i++) {
            long long ab = time[i];

            while (aage < peeche && kabTak[aage] <= ab) {
                aage++;
                charge++;
            }

            if (charge == 0) {
                hoGaya = 0;
                break;
            }

            charge--;

            long long shuru;
            if (aage == peeche) {
                shuru = ab;
            } else {
                if (ab > lastWala) shuru = ab;
                else shuru = lastWala;
            }

            long long khatam = shuru + r;
            kabTak[peeche] = khatam;
            peeche++;
            lastWala = khatam;
        }

        if (hoGaya == 1) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}