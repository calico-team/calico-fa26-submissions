#include <iostream>
#include <vector>
#include <climits>
#define int long long
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int flag = false;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (i > 1) {
                if (a[i] - a[i - 1] < r && a[i - 1] - a[i - 2] < r) {
                    flag = true;
                    break;
                }
            }
            if (i > 2) {
                if (a[i] - a[i - 1] < r && a[i - 2] - a[i - 3] < r) {
                    flag = true;
                    break;
                }
            }
        }
    }
    if (flag) cout << "NO" << endl;
    else cout << "YES" << endl;
}

signed main() {
	int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
