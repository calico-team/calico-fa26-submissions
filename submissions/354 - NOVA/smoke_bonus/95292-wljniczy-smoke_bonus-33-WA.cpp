#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long r;
    cin >> n >> r;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cnt = 2;
    long long finish = 0;
    for (int i = 0; i < n; i++) {
        if (cnt == 0 && a[i] >= finish) {
            cnt++;
        }
        if (cnt == 0) {
            cout << "NO"<<endl;
            return;
        }
        cnt--;
        if (cnt == 0) {
            finish = max(finish, a[i]) + r;
        } else {
            finish = a[i] + r;
        }
    }
    cout << "YES"<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
