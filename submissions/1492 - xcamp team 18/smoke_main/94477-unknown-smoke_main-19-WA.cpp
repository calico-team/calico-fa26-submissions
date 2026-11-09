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
    int t_a = 0, t_b = INT_MAX;
    int flag = false;
    for (int i = 1; i < n; i++) {
        t_a += a[i] - a[i - 1];
        if (t_a >= r) t_b += r - t_a;
        if (t_a >= r && t_b >= r) {
            if (t_b >= r) {
                t_b = 0;
            } else {
                t_a = 0;
            }
        } else if (t_a >= r) {
            t_a = 0;
        } else if (t_b >= r) {
            t_b = 0;
        } else {
            flag = true;
            break;
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
