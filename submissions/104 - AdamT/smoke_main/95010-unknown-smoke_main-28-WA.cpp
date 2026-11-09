#include <iostream>

using namespace std;

int n, r, a[int(1e5 + 10)];
void solve() {
    cin >> n >> r;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int t1, t2;
    t1 = t2 = -1;
    int charge = 2;
    for (int i = 0; i < n; i++) {
        if (t1 != -1 && a[i] >= t1) {
            charge++;
            t1 = -1;
        }
        // if (t2 != -1 && a[i] >= t2) {
        //     charge++;
        //     t2 = -1;
        // }
        if (charge > 0) {
            charge--;
            if (t1 == -1) {
                t1 = a[i] + r;
            }
        } else {
            cout << "NO" << '\n';
            return;
        }
        // cout << charge << ' ' << a[i] << ' ' << t1 << '\n';
    }
    cout << "YES" << '\n';
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
