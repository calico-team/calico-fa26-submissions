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
        long long nfir = 0;
        long long nsec = 0;
        long long last = 9;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            if (!fir && a[i] >= nfir) {
                //cout << 3 << " ";
                fir = 1;
            }
            if (!sec && a[i] >= nsec) {
                //cout << 4 << " ";
                sec = 1;
            }
            if (fir) {
                //cout << 1 << " ";
                fir = 0;
                nfir = max(last, (long long)a[i]) + r;
                last = nfir;
            } else if (sec) {
                //cout << 2 << " ";
                sec = 0;
                nsec = max(last, (long long)a[i]) + r;
                last = nsec;
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