#include <iostream>
using namespace std;

int main() {
    int test;
    cin >> test;
    while (test--) {
        int n, r;
        cin >> n >> r;

        int time[100005];
        for (int i = 0; i < n; i++) {
            cin >> time[i];
        }

        int charge = 2;
        int kabTak[100005];
        int aage = 0, peeche = 0;
        int lastWala = 0;
        int hoGaya = 1; // 1 matlab YES

        for (int i = 0; i < n; i++) {
            int ab = time[i];

            // pehle dekho koi purana recharge to pura nahi ho gaya
            while (aage < peeche && kabTak[aage] <= ab) {
                aage++;
                charge++;
            }

            // agar charge hi nahi bacha to fail
            if (charge == 0) {
                hoGaya = 0;
                break;
            }

            // ek smoke phenko
            charge--;

            // naya recharge kab shuru hoga?
            int shuru;
            if (aage == peeche) {
                shuru = ab;
            } else {
                if (ab > lastWala) shuru = ab;
                else shuru = lastWala;
            }

            int khatam = shuru + r;
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