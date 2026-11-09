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
        int minn = INT_MAX;
        cin >> a[1];
        for (int i = 2; i <= n; i++) {
            cin >> a[i];
            minn = min(minn, a[i] - a[i - 1]);
        }
        if (minn >= r) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}