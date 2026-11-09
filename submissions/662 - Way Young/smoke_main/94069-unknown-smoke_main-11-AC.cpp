#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, r;
    cin >> n >> r;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    int s1, s2;
    s1 = 0;
    s2 = r;
    for (int i = 1; i < n; i++) {
        int tu = 0;
        tu = min(s1, nums[i]-nums[i-1]);
        s1 -= tu; 
        int tu2 = min(s2, nums[i]-nums[i-1]-tu);
        s2 -= tu2;
        bool done = false;
        if (s1 == 0) {
            s1 = r;
            done = true;
        }
        if (!done && s2 == 0) {
            s2 = r;
            done = true;
        }
        if (!done) {
            cout << "NO\n";
            return;
        }
        if (s2 < s1) swap(s1, s2);
    }
    cout << "YES\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tcs;
    cin >> tcs;
    while (tcs--) solve();
    cout.flush();
}   