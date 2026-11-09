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

void solve() {
    int n, r;
    cin >> n >> r;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int c = 2;
    int tot = 0;
    int pre = a[0];
    for (int x : a) {
        tot += x - pre;
        if (c <= 1 && tot >= r) {
            tot -= r;
            c++;
        }
        if (c == 1 && tot >= r) {
            tot -= r;
            c++;
        }
        if (c == 2) {
            tot = 0;
        } 

        if (c == 0) {
            cout << "NO";
            return;
        }

        c--;
        pre = x;
    }

    cout << "YES";
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve(), cout << endl;
    }

    return 0;
}