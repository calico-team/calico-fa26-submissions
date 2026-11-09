#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> nums(n);
    for (int& x : nums) cin >> x;
    int amt = 2, next = INT_MAX / 2;
    for (int x : nums) {
        while (next <= x && amt < 2) {
            amt++;
            next += r;
        }
        if (amt == 0) {
            cout << "NO\n";
            return;
        }
        if (amt == 2) {
            next = x + r;
        }
        amt--;
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}