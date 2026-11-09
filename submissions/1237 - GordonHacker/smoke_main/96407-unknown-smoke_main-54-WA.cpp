#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N];
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, r;
        cin >> n >> r;
        bool flag = 1;
        bool fir = 1;
        bool sec = 1;
        int nfir = 0;
        int nsec = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            if (!fir && a[i] - nfir >= r) {
                //cout << 3 << " ";
                fir = 1;
                nsec = nfir + r;
            }
            if (!sec && a[i] - nsec >= r) {
                //cout << 4 << " ";
                sec = 1;
            }
            if (fir) {
                //cout << 1 << " ";
                fir = 0;
                nfir = a[i];
            } else if (sec) {
                //cout << 2 << " ";
                sec = 0;
                nsec = a[i];
            } else {
                flag = 0;
                break;
            }
        }
        if (flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}