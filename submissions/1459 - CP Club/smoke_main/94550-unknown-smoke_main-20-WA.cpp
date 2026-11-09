#include <iostream>
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    int ai[n] = {};
    for (int i = 0; i < n; i++) cin >> ai[i];
    int count = 2;
    int start_charge = -1;
    for (int i = 0; i < n; i++) {
        int cur = ai[i];
        while (start_charge != -1 && cur - start_charge >= r) {
            if (count >= 2) {
                start_charge = -1;
                break;
            }
            start_charge += r;
            count++;
        }
        if (count == 0) {
            cout << "NO" << endl;
            return;
        }
        count--;
        if (start_charge == -1) start_charge = cur;
    }
    cout << "YES" << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}