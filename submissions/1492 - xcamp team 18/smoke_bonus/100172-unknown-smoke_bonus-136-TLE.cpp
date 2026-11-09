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
    int t_a = 0, t_b = r;
    int flag = false;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            if (t_a + a[i] - a[i - 1] >= r) {
                if (t_a >= r) {
                    t_b += a[i] - a[i - 1];
                } else {
                    t_b += a[i] - a[i - 1] - (r - t_a);
                }
                t_a = 0;
            } else if (t_b + a[i] - a[i - 1] >= r) {
                if (t_b >= r) {
                    t_a += a[i] - a[i - 1];
                } else {
                    t_a += a[i] - a[i - 1] - (r - t_b);
                }
                t_b = 0;
            } else {
                flag = true;
                break;
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
