#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ull = unsigned long long;
void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int start = 2 * r;
    int curr = 0;
    for (int time : a) {
        start = min(2 * r, start + time - curr);
        if (start < r) {
            cout << "NO\n";
            return;
        }
        start -= r;
        curr = time;
    }
    cout << "YES\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}