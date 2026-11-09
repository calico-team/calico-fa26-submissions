#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

string query(char c, int n) {
    cout << string(n, c) << endl;

    string res;
    cin >> res;

    return res;
}

string answer(string ans) {
    cout << ans << endl;

    string res;
    cin >> res;

    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<char> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    string ans(n, '.');
    for (char c : a) {
        string res = query(c, n);

        if (res == "CORRECT") return;

        for (int i = 0; i < n; i++) {
            if (res[i] != '_') {
                ans[i] = c;
            }
        }
    }

    answer(ans);
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve();
    }

    return 0;
}