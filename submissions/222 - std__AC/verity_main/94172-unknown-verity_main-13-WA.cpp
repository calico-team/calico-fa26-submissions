#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200;
char arr[300];
int locs[N];
bitset<300> bs;
int t, n, k;

bool solve() {
    for (int i = 1; i <= n; i++) {
        locs[i] += !bs[i];
        cout << arr[locs[i]];
    }
    cout << endl;
    string ans;
    cin >> ans;
    if ("CORRECT" == ans) return true;
    for (int i = 1; i <= n; i++) {
        bs[i] = bs[i] || ans[i - 1] != '_';
    }
    return false;
}

signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= k; i++) {
            cin >> arr[i];
        }
        bs.reset();
        while (!solve());
    }
    return 0;
}