#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> nums(n);
    for (int& x : nums) cin >> x;
    int amt = 2, t = 0;
    int prev = 0;
    for (int x : nums) {
        t -= x - prev;
        while (t < 0 && amt < 2) {
            amt++;
            t += r;
        }
        if (amt == 2) t = 0;
        if (amt == 0) {
            cout << "NO\n";
            return;
        }
        if (amt == 2) t = r;
        amt--;
        prev = x;
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